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

        std::cout << "Conectado al servidor con WebnSockets " << std::endl;




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

