// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <mysql/mysql.h>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include <string>
#include <iostream>

#include "EmpleadoRepositorio.h"

#define SERVER "localhost"
#define USER "antonio"
#define PASS "antonio"
#define BD "empresa3"
#define PORT 3307

void testRepositorio() {
    // Crear la sesion de soci:
    try {
        soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

        EmpleadoRepositorio repo(sql);

        // Recuperar un empleado con el id:
        auto resul1 = repo.read(100);

        if (resul1) {
            std::cout << resul1->id << " " << resul1->nombre << " " << resul1->cargo << std::endl;
        }
        else {
            std::cout << "No existe el empleado" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void testMySQL() {
	MYSQL* con;

	// Inicializar la conexion;
	con = mysql_init(nullptr);
	if (!mysql_real_connect(con, SERVER, USER, PASS, BD, PORT, nullptr, 0)) {
		std::cerr << "Error al conectar" << std::endl;
		return;
	}

	std::cout << "Conectado a Mysql" << std::endl;
	mysql_close(con);
}

void testRecuperarConsulta() {
    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;

    // Conexión
    con = mysql_init(nullptr);
    if (!mysql_real_connect(con, SERVER, USER, PASS, BD, PORT, nullptr, 0)) {
        std::cerr << "Error de conexión: " << mysql_error(con) << std::endl;
        return;
    }

    // Consulta directa sin parámetros
    const char* query = "SELECT id, nombre, cargo FROM empleados";
    if (mysql_query(con, query)) {
        std::cerr << "Error en la consulta: " << mysql_error(con) << std::endl;
        mysql_close(con);
        return;
    }

    // Obtener resultados
    res = mysql_store_result(con);
    if (!res) {
        std::cerr << "Error al obtener resultados: " << mysql_error(con) << std::endl;
        mysql_close(con);
        return;
    }

    // Mostrar resultados
    std::cout << "ID;Nombre;Cargo\n";
    while ((row = mysql_fetch_row(res))) {
        std::cout << row[0] << ";" << row[1] << ";" << row[2] << "\n";
    }

    // Limpieza
    mysql_free_result(res);
    mysql_close(con);
}

void testInsertar() {
    MYSQL* con;
    MYSQL_STMT* stmt;
    MYSQL_BIND bind[3]; // un array con tantas posiciones como parametros tengamos

    // Datos a insertar
    int id = 10;
    const char* nombre = "Laura Gómez";
    const char* cargo = "Analista";

    // Conexión
    con = mysql_init(nullptr);
    if (!mysql_real_connect(con, SERVER, USER, PASS, BD, PORT, nullptr, 0)) {
        std::cerr << "Error de conexión: " << mysql_error(con) << std::endl;
        return;
    }

    // Preparar sentencia
    const char* query = "INSERT INTO empleados (id, nombre, cargo) VALUES (?, ?, ?)";
    stmt = mysql_stmt_init(con);
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Error al preparar la sentencia: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    // Vincular parámetros
    memset(bind, 0, sizeof(bind));

    // id
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char*)&id;
    bind[0].is_null = 0;
    bind[0].length = 0;

    // nombre
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)nombre;
    bind[1].buffer_length = strlen(nombre);
    bind[1].is_null = 0;
    bind[1].length = 0;

    // cargo
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char*)cargo;
    bind[2].buffer_length = strlen(cargo);
    bind[2].is_null = 0;
    bind[2].length = 0;

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "Error al vincular parámetros: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    // Ejecutar
    if (mysql_stmt_execute(stmt)) {
        std::cerr << "Error al ejecutar la sentencia: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    std::cout << "Fila insertada correctamente." << std::endl;

    // Limpieza
    mysql_stmt_close(stmt);
    mysql_close(con);
}

int main()
{
	//testMySQL();
    //testRecuperarConsulta();
    //testInsertar();
    testRepositorio();
}

