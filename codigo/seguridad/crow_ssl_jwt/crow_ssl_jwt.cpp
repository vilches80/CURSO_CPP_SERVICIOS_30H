// crow_ssl_jwt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include <chrono>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define USER "admin"
#define PWD "1234" 

/*
Desde postman enviamos:
{
   "usuario":"admin",
   "password":"1234"
}

*/

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req) {
        // Recoger de la Request el usuario / password enviado

        try {
            auto j = json::parse(req.body);
            // Validar si es correcto, si no -> 401
            if (j.at("usuario") == USER && j.at("password") == PWD) {

                // Generar el token: para ver lo que genera, devolver el token al cliente
                auto token = jwt::create().
                    set_issuer("Curso C++").
                    set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes(30)).
                    sign(jwt::algorithm::hs256(PWD));

                crow::json::wvalue respuesta;
                respuesta["token"] = token;
                return crow::response(respuesta);
            }
            else {
                crow::response(400, "Credenciales incorrectas");
            }
        }
        catch (const std::exception& ex) {
            return crow::response(500, std::string(ex.what()));
        }
    });

    app.ssl_file("..\\certificados\\cert.pem", "..\\certificados\\key.pem")
        .port(443)
        .multithreaded()
        .run();

}