// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <mysql/mysql.h>
#include <string>
#include <iostream>

#define SERVER "localhost"
#define USER "antonio"
#define PASS "antonio"
#define BD "empresa3"
#define PORT 3307

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


int main()
{
	testMySQL();
}

