// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <mysqlx/xdevapi.h>


void testConexion() {
    try {
        mysqlx::Session sesion("localhost", 33060, "root", "antonio");
        std::cout << "Conexion ok" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

}

int main()
{
    testConexion();
    
    return 0;
}

