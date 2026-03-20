// multicliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

// Sesión por cliente
class session : public std::enable_shared_from_this<session> {

    // Atributos privados

    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    http::response<http::string_body> res_;

public:
    explicit session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() { read_request(); }

private:
    void read_request() {
        // Obtiene un std::shared_ptr que apunta a la clase actual:
        auto self = shared_from_this();

        // La lambda de ejecuta cuando termina la lectura:
        http::async_read(socket_, buffer_, req_,
            [self](beast::error_code ec, std::size_t) {
                if (!ec) self->handle_request();
            });
    }

    void handle_request() {
        res_.version(req_.version()); // Copiar la version del protocolo
        res_.keep_alive(req_.keep_alive());
        res_.result(http::status::ok);
        res_.set(http::field::server, "Boost.Beast");
        res_.set(http::field::content_type, "text/plain");
        res_.body() = "Mensaje del servidor";
        res_.prepare_payload();
        write_response();
    }

    void write_response() {
        // Obtiene un std::shared_ptr que apunta a la clase actual:
        auto self = shared_from_this();

        // Cuando termina la escritura se cierra la conexion:
        http::async_write(socket_, res_,
            [self](beast::error_code ec, std::size_t) {
                self->socket_.shutdown(tcp::socket::shutdown_send, ec);
            });
    }
};

//  Acepta conexiones TCP
void do_accept(tcp::acceptor& acceptor) {
    // Aceptar al cliente de forma asincrona
    acceptor.async_accept(
        [&acceptor](beast::error_code ec, tcp::socket socket) {
            // Si no hay error crea una nueva instancia de session para leer peticion, responder etc.
            if (!ec) std::make_shared<session>(std::move(socket))->start();
            do_accept(acceptor); // Recursivo para aceptar más clientes
        });
}

int main() {
    try {
        // numero de hilos que lo ejecutan: es solo una sugerencia
        asio::io_context ioc{ 1 };

        tcp::endpoint endpoint{ tcp::v4(), 8080 };
        tcp::acceptor acceptor{ ioc, endpoint };

        do_accept(acceptor);
        std::cout << "Servidor escuchando en puerto 8080...\n";


        /* Elegir u hilo o varios */

        // Solo lo llama un hilo 
        //ioc.run();

        // O si lo queremos multihilo:
        std::vector<std::thread> threads;
        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.emplace_back([&ioc] { ioc.run(); });
        }
        for (auto& t : threads) t.join();

        //////////////////////////////////

    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

