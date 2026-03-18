// wsservidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

void servidorWS() {
    try {
        // Definir el contexto de io:
        asio::io_context ioc;

        // Crear el socket de escucha;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));
        std::cout << "Servidor WS escuchando en el puerto 8080" << std::endl;

        for (;;) {
            // Aceptar la conexion, al aceptar la conexion se devuelve otro socket
            tcp::socket socket(ioc);

            // Acepta la conexion de un cliente:
            acceptor.accept(socket);
            std::cout << "Cliente aceptado ..." << std::endl;

            // Crear el socket stream;
            websocket::stream<tcp::socket> ws(std::move(socket));

            // Realizar el handshake:
            ws.accept();

            // Bucle de comunicacion con ese cliente: Servidor de eco:
            for (;;) {
                // Definir un buffer:
                beast::flat_buffer buffer;
                ws.read(buffer);

                // Se convierte los datos del buffer a string:
                std::string msg = beast::buffers_to_string(buffer.data());
                std::cout << "Mensaje recibido: " << msg << std::endl;

                // Contestar al cliente: hacer eco!
                ws.write(asio::buffer(msg));
            }
        }

    }
    catch (beast::system_error const& err){
        if (err.code() == websocket::error::closed) {
            std::cout << "Cerrando comunicacion con el cliente" << std::endl;
        }
        else {
            std::cerr << "ERROR: " << "Error en WebSocket << " << err.code().message() << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
}


int main()
{
    servidorWS();
    return 0;
}

