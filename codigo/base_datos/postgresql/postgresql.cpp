// postgresql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <libpq-fe.h>
#include <vector>

#include "Categoria.h"
#include "CategoriaRepositorio.h"

int testConexion() {
    const char* conninfo = "host=127.0.0.1 port=5433 dbname=empresa3 user=antonio password=antonio";

    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Error de conexión: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }

    std::cout << "Conexion exitosa a PostgreSQL" << std::endl;

    PQfinish(conn);
}

void testRepositorio() {
    const char* conninfo = "host=127.0.0.1 port=5433 dbname=empresa3 user=antonio password=antonio";

    CategoriaRepositorio repo(conninfo);

    // selectAll()
    std::vector<Categoria> categorias = repo.selectAll();
    for (const auto& c : categorias) {
        std::cout << c.id << " " << c.nombre << std::endl;
    }  

    std::cout << "---------------" << std::endl;

    // Read:
    int id = 7;
    auto cat = repo.read(id);
    if (cat) {
        std::cout << cat->id << " " << cat->nombre << " " << std::endl;
        cat->nombre = "Solo frutas";
        repo.update(*cat);
    }
    else {
        std::cout << "No se encuentra la categoria " << id << std::endl;
    }

    // Delete: 
    repo.deleteid(9);
}

int main()
{
    //testConexion();
    testRepositorio();
    return 0;
}

