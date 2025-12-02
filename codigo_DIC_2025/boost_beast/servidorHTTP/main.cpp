// servidorHTTP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include "ServidorHTTP.h"

void testServidorHTTP() {
    boost::asio::io_context ioc;
    ServidorHTTP server(ioc, 8080);
    server.run();
}

int main()
{
    testServidorHTTP();
    return 0;
}

