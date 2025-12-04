// peticion_respuesta_cliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include <zmq.hpp>
#include <string>
#include "Persona.h"

int main()
{
    try {
        // Creamos el contexto indicando el numero de hilos
        zmq::context_t contexto(1);

        // Creamos el socket seleccionando el tipo de patron a implementar:
        zmq::socket_t socket(contexto, zmq::socket_type::req);
        socket.connect("tcp://localhost:5555");

        // Definir el objeto persona:
        Persona p{ "Juan", 45, true };

        // Convertir el objeto en json y lo enviamos al servidor:
        nlohmann::json j = p;
        std::string mensaje = j.dump();

        // Enviamos con send indicando que solo tiene una parte el mensaje:
        socket.send(zmq::buffer(mensaje), zmq::send_flags::none);

        zmq::message_t response;
        socket.recv(response, zmq::recv_flags::none);

        std::cout << "Respuesta del servidor: " << response.to_string() << std::endl;           

    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return 0;
}