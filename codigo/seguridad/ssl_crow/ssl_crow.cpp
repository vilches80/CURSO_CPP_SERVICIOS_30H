// ssl_crow.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>

/*
probar: 
curl https//localhost --insecure 
no deberia de dar error y luego probar 
curl https://localhost  
por defecto ya toman el puerto 443, 

probar despues: curl http://localhost
*/

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hola seguro con HTTPS";
    });

    app.ssl_file("..\\certificados\\cert.pem","..\\certificados\\key.pem")
        .port(443)
        .multithreaded()
        .run();

}

