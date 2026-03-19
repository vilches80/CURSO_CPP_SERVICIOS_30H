// wscliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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


void clienteWS() {
    try {
        // Definir el contexto de io:
        asio::io_context ioc;

        // Resolver DNS para localhost:
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve("127.0.0.1", "8080");

        // Crear el WS:
        websocket::stream<tcp::socket> ws(ioc);

        // Conectar al servidor:
        asio::connect(ws.next_layer(), results.begin(), results.end());
        
        // Handshake:
        ws.handshake("127.0.0.1", "/");

        std::cout << "Conectado al servidor con WebSockets " << std::endl;

        // Enviamos un mensaje al servidor:
        std::string mensaje = "Hola desde el cliente";
        ws.write(asio::buffer(mensaje));

        // Leer la respuesta: necesitamos un buffer:
        beast::flat_buffer buffer;
        ws.read(buffer);

        // Obtener la respuesta del servidor:
        std::cout << "Respuesta del servidor: " << beast::buffers_to_string(buffer.data()) << std::endl;

        // cerrar la conexion:
        ws.close(websocket::close_code::normal);

    }
    catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
}

int main()
{
    clienteWS();
    return 0;
}

