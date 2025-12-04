// push_pull_dispatcher.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <zmq.hpp>
#include <string>

int main()
{
    // Subcriptor, filtra los mensajes de un topic:

    // Crear el socket y el contexto:
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::push);

    // Conectar al puerto:
    socket.bind("tcp://localhost:5557");

    std::cout << "Enviar tareas ...." << std::endl;

    for (int i = 0; i < 10; i++) {
        socket.send(zmq::buffer("Tarea " + std::to_string((i + 1))), zmq::send_flags::none);
    }

    return 0;
}
