// tokens_jwt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <chrono>
#include <crow.h>

#include <nlohmann/json.hpp>
#include <jwt-cpp/jwt.h>

using json = nlohmann::json;

#define USER "admin"
#define PWD "1234"


int main()
{
    crow::SimpleApp app;
        
    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& request) {

        try {

            // Obtener las credenciales de la request:
            auto j = json::parse(request.body);
            if (!j.contains("user") || !j.contains("pwd")) {
                return crow::response(400, std::string("Json incorrecto: se esperaban campos");
            }

            // Comprobar las credenciales: (ir al Repositorio)
            if (USER == j.at("user") && PWD == j.at("pwd")) {
                // Esta correcto, creamos el token:
                auto token = jwt::create().
                    set_issuer("curso C++").
                    set_payload_claim("usuario", jwt::claim(USER)).
                    set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes{ 30 }).
                    sign(jwt::algorithm::hs256{ PWD });

                // Devolver el token al cliente:
                crow::json::wvalue respuesta;
                respuesta["token"] = token;
                return crow::response(respuesta);

            }
            else {
                return crow::response(400, "Credenciales incorrectas");
            }

        }
        catch (const std::exception& e) {
            return crow::response(400, std::string("Json incorrecto: ") + e.what());
        }

        });

    // Poner en marcha el servidor:
    //app.multithreaded().run();
    app.multithreaded().concurrency(std::thread::hardware_concurrency()).port(8000).run();
    return 0;
}

