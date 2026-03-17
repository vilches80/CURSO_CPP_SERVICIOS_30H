// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include <thread>

void testCrow() {
    crow::SimpleApp app;
    
    // Configuracion de rutas:
    CROW_ROUTE(app, "/")([]() {
        return "Hello World";
    });

    CROW_ROUTE(app, "/info")([]() {
        crow::json::wvalue resp;

        // Definiendo las claves de la respuesta:
        resp["mensaje"] = "Respuesta desde Crow";
        resp["estado"] = "ok";
        resp["codigo"] = 200;
        return crow::response{ resp };
    });

    CROW_ROUTE(app, "/operar").methods(crow::HTTPMethod::GET)
        ([](const crow::request& req) {
        return crow::response(req.body);
        });

    CROW_ROUTE(app, "/operar/<int>/<int>").methods(crow::HTTPMethod::GET)
        ([](const crow::request& req, int a, int b) {
            crow::json::wvalue resp;

            int sum = a + b;
            resp["a"] = a;
            resp["b"] = b;
            resp["suma"] = a + b;

            return crow::response{ resp };
        });

    // Iniciar el servicio en el puerto
    app.port(18000);

    // Activar multihilo:
    app.multithreaded();
    
    // Numero de hilo a utilizar:
    app.concurrency(std::thread::hardware_concurrency());
     
    // Al final, arrancamos la aplicación
    app.run();

    // app.port(18000).run();
}


int main()
{
    testCrow();
    return 0;
}

