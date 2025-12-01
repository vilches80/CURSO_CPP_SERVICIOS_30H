// servicio_crow.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>

void testCrow() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });
    app.port(18080).run();
}


int main() {
    testCrow();
    return 0;
}

