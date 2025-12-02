#include "ServidorREST.h"
// ServidorREST.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

ServidorREST::ServidorREST(net::io_context&, unsigned int port):ioc(ioc), acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {}

void ServidorREST::run() {

}

ServidorREST::~ServidorREST()
{
}
