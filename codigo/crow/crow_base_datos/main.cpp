// crow_base_datos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>

#include "CategoriaCrow.h"
#include "CategoriaRepositorio.h"


int main()
{
	const char* conninfo = "host=127.0.0.1 port=5433 dbname=empresa3 user=antonio password=antonio";
	CategoriaRepositorio repo(conninfo);
	CategoriaCrow servicio(repo);
	servicio.run();
	return 0;
}

