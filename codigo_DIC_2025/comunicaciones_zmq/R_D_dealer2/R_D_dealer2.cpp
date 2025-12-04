// R_D_dealer2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <iostream>
#include <zmq.hpp>
#include <string>
#include <vector>

int main()
{
    // Crear el socket y el contexto:
    zmq::context_t contexto(1);
    zmq::socket_t dealer(contexto, zmq::socket_type::dealer);

    // Configurar el socket para asignar el idcliente:
    dealer.set(zmq::sockopt::routing_id, "cliente_2");

    // conectar al puerto:
    dealer.connect("tcp:://localhost:5559");

    std::cout << "Conectado al puerto: 5555" << std::endl;
    std::string mensaje = "soy el cliente 2";
    dealer.send(zmq::message_t(mensaje), zmq::send_flags::none);
    std::cout << "mensaje enviado" << std::endl;

    // Esperar la respuesta:
    zmq::message_t respuesta;
    dealer.recv(respuesta);

    std::cout << "Respuesta del servidor " << respuesta.to_string() << std::endl;

    return 0;

}