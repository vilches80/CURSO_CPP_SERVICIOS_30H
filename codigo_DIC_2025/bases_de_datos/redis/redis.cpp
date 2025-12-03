// redis.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <hiredis/hiredis.h>

int main()
{
    // Establecer la conexión con el contenedor:
    redisContext* contexto = redisConnect("127.0.0.1", 6379);
    if (contexto == nullptr || contexto->err) {

        if (contexto) {
            std::cerr << "Error de conexion: " << contexto->errstr << std::endl;
        }
        else {
            std::cerr << "Error en el contexto " << std::endl;

        }

        return 1;
    }

    // Probar comandos:
    redisReply* reply = (redisReply*)redisCommand(contexto, "SET apellidos Gonzalez");
    std::cout << "SET respuesta : " << reply->str << std::endl;
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(contexto, "GET nombre");
    std::cout << "SET respuesta : " << reply->str << std::endl;
    freeReplyObject(reply);

    // Liberar el contexto de la conexion:
    redisFree(contexto);
    return 0;
}

