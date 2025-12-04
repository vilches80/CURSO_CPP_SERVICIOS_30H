// pub_sub_subcriptor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <iostream>
#include <zmq.hpp>
#include <string>

int main()
{
    // Subcriptor, filtra los mensajes de un topic:
    
    // Crear el socket y el contexto:
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::sub);

    // Conectar al puerto:
    socket.connect("tcp://localhost:5556");

    // Para filtrar por un topic:
    socket.set(zmq::sockopt::subscribe, "temperatura");

    while (true) {
        zmq::message_t mensaje;

        // Recibir:
        socket.recv(mensaje);
        std::string medida = mensaje.to_string();

        std::cout << "Recibido: " << medida << std::endl;
    }

    return 0;
}
