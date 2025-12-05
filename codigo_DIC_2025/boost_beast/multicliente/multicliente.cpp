// multicliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <memory>

#include <boost/beast/core.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace http = beast::http;
using tcp = net::ip::tcp;

class session : public std::enable_shared_from_this<session> {

	// Atributos de la session:
	tcp::socket socket_;
	beast::flat_buffer buffer;
	http::request<http::string_body> request;
	http::response<http::string_body> response;

public:
	session(tcp::socket socket):socket_(std::move(socket)){}
	void start() { read_request(); }

private:
	void read_request() {
		// Obtener un std::shared_ptr que apunta a la clase actual:
		auto self = shared_from_this();

		// Hacemos una lectura sincrona:
		http::async_read(socket_, buffer, request, [self](beast::error_code ec, std::size_t) {
			if (!ec) {
				self->handler_request();
			}
		});

	}
	void handler_request() {
		// Analizar la peticion, operaciones ...
		std::string respuesta;

		respuesta = "URL: " + std::string(request.target()) + " Method: " + std::string(request.method_string());

		// Montar la respuesta al cliente: se copia la version del protocolo y el tipo de conexion a la respuesta
		response.version(request.version());
		response.keep_alive(request.keep_alive());
		response.result(http::status::ok);

		// Configurar las cabeceras: http
		response.set(http::field::server, "Boost.asio");
		response.set(http::field::content_type, "text/plain");

		// En el body cargamos la respuesta:
		response.body() = respuesta;

		// Calcular el tamaño de la respuesta:
		response.prepare_payload();

		// Escribir:
		this->write_response();

	}

	void write_response() {
		// Obtener un std::shared_ptr que apunta a la clase actual:
		auto self = shared_from_this();

		// Hacemos una escritura asincrona:
		http::async_write(socket_, response, [self](beast::error_code ec, std::size_t) {
			// Cerrar la conexion:
			self->socket_.shutdown(tcp::socket::shutdown_send, ec);
		});
	}

};


void do_accept(tcp::acceptor& acceptor) {
	
	// Aceptar al cliente de forma asincrona:
	acceptor.async_accept([&acceptor](beast::error_code ec, tcp::socket socket) {

		// Si no hay error, creamos una nueva sesion:
		if (!ec) {

			// Crear y arrancar la sesion:
			std::make_shared<session>(std::move(socket))->start();
		}

		// Llamada recursiva para continuar aceptando clientes:
		do_accept(acceptor);
	});
}


int main()
{
	net::io_context ioc;

	// Inicializar acceptor con el contexto de entrada/salida y un endpoint en el puerto 80
	tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

	do_accept(acceptor);

	std::cout << "Servidor multicliente en el puerto 8080" << std::endl;

	// DEfinir un vector para lanzar los hilos:
	std::vector<std::thread> hilos;
	for (int i = 0; i < std::thread::hardware_concurrency(); i++) {

		// Creamos un hilo dentro del vector sin hacer una copia:
		hilos.emplace_back([&ioc] { ioc.run();  });
	}

	for (auto& h : hilos) {
		h.join();
	}

	// SI SOLO QUEREMOS UN HILO EN EJECUCION
	//ioc.run()

	return 0;
}
