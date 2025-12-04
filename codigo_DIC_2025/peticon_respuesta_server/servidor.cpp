// peticon_respuesta_server.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include <zmq.hpp>
#include "Persona.h"

int main()
{
    // Creamos el contexto indicando el numero de hilos
    zmq::context_t contexto(1);

    // Creamos el socket seleccionando el tipo de patron a implementar:
    zmq::socket_t socket(contexto, zmq::socket_type::rep);

    // Hace un bind el puerto:
    socket.bind("tcp://*:5555");

    std::cout << "Servidor zmq rep en el puerto 5555" << std::endl;
    while (true) {
        zmq::message_t request;

        // Esperando el mensaje del cliente: SINCRONO -> BLOQUEANTE
        socket.recv(request, zmq::recv_flags::none); // Es un mensaje de una sola parte

        // Parseamos el mensaje con json:
        nlohmann::json j = nlohmann::json::parse(request.to_string());
        Persona p = j.get<Persona>();

        std::cout << "Persona recibida: " << p.nombre << " " << p.edad << std::endl;

        // Enviamos respuesta al cliente:
        std::string respuesta = request.to_string();
        socket.send(zmq::buffer(respuesta), zmq::send_flags::none);
    }
    return 0;
}

