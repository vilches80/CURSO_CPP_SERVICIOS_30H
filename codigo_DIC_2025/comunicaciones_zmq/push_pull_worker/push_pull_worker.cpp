// push_pull_worker.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <zmq.hpp>
#include <string>

int main()
{
    // Subcriptor, filtra los mensajes de un topic:

    // Crear el socket y el contexto:
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::pull);

    // Conectar al puerto:
    socket.connect("tcp://localhost:5557");

    while (true) {
        zmq::message_t mensaje;

        socket.recv(mensaje, zmq::recv_flags::none);
        std::cout << "Recibido: " << mensaje.to_string() << std::endl;
    }

    return 0;
}