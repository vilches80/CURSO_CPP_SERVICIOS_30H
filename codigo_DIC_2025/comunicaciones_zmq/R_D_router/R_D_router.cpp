// R_D_router.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <zmq.hpp>
#include <string>
#include <vector>

int main()
{
    // Crear el socket y el contexto:
    zmq::context_t contexto(1);
    zmq::socket_t router(contexto, zmq::socket_type::router);

    // Bind al puerto:
    router.bind("tcp:://*:5559");

    zmq::message_t parte;
    std::vector<zmq::message_t> partes;
    int n = 2;

    std::cout << "Router preparado ..." << std::endl;

    while (true) {
        
        // Limpiar el vector antes de recibir:
        partes.clear();

        // Recibir las partes del mensaje:
        for (int i = 0; i < n; i++) {
            router.recv(parte);
            std::cout << "Parte[" << i << "] = " << parte.to_string() << std::endl;

            // Guardamos en el vector la parte del mensaje:
            partes.push_back(std::move(parte));
        }

        // Recoger clienteId y payload:
        std::string clienteId = partes[0].to_string();
        std::string payload = partes[1].to_string();

        std::cout << "Mensaje de " << clienteId << " " << payload << std::endl;

        // Respondemos al cliente:
        router.send(zmq::buffer(clienteId), zmq::send_flags::sndmore); // primera parte!
        router.send(zmq::buffer("Respuesta del server"), zmq::send_flags::none); // la ultima parte
        
    }
    return 0;
}