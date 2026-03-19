#include <stdexcept>

#include "CategoriaRepositorio.h"

CategoriaRepositorio::CategoriaRepositorio(std::string cadconex)
{
	this->conn = PQconnectdb(cadconex.c_str());
	if (PQstatus(conn) != CONNECTION_OK) {
		PQfinish(conn);
		std::string mensaje = PQerrorMessage(conn);

		throw std::runtime_error("Error en la conexion: " + mensaje);		
	}
}

std::optional<Categoria> CategoriaRepositorio::read(int id)
{
	std::string query = "SELECT id, nombre FROM tbcategorias WHERE id = " + std::to_string(id);
	PGresult* res = PQexec(conn, query.c_str());

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		PQclear(res);
		throw std::runtime_error("Error al recuperar la categoria con id "+std::to_string(id));
	}

	if (PQntuples(res) == 0) {
		// No hay resultados:
		PQclear(res);
		return std::nullopt;
	}

	Categoria c;
	c.id = std::stoi(PQgetvalue(res, 0, 0));
	c.nombre = PQgetvalue(res, 0, 1);

	PQclear(res);
	return c;
}

int CategoriaRepositorio::create(const Categoria& categoria)
{
	return 0;
}

int CategoriaRepositorio::update(const Categoria& cat)
{
	const char* query = "UPDATE tbcategorias SET nombre = $1 WHERE id = $2";

	// Array de parametros
	const char* paramValues[2];
	paramValues[0] = cat.nombre.c_str();	
	std::string idStr = std::to_string(cat.id);
	paramValues[1] = idStr.c_str();

	PGresult* res = PQexecParams(
		conn,
		query,
		2,              // número de parámetros
		nullptr,        // tipos de parámetros (NULL = inferidos)
		paramValues,    // valores
		nullptr,        // longitudes (NULL para texto)
		nullptr,        // formatos (NULL = texto)
		0               // resultado en texto (0) o binario (1)
	);

	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::string errorMsg = PQerrorMessage(conn);
		PQclear(res);
		throw std::runtime_error("Error al actualizar categoria: " + errorMsg);
	}

	int filas = std::stoi(PQcmdTuples(res));
	PQclear(res);

	return filas;
}

int CategoriaRepositorio::deleteid(int id)
{
	std::string query = "DELETE FROM tbcategorias WHERE id = " + std::to_string(id);
	PGresult* res = PQexec(conn, query.c_str());

	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		PQclear(res);
		throw std::runtime_error("Error al eliminar la categoria: "+std::to_string(id));
	}

	int filas = std::stoi(PQcmdTuples(res));
	PQclear(res);

	return filas;
}

std::vector<Categoria> CategoriaRepositorio::selectAll()
{
	std::vector<Categoria> categorias;
	PGresult* res = PQexec(conn, "select id, nombre from tbcategorias");

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		PQclear(res);
		throw std::runtime_error("Error al listar categorias");
	}

	int rows = PQntuples(res);
	for (int i = 0; i < rows; i++) {
		Categoria cat;
		cat.id = std::stoi(PQgetvalue(res, i, 0));
		cat.nombre = PQgetvalue(res, i, 1);
		categorias.push_back(cat);
	}
	PQclear(res);
	return categorias;
}

CategoriaRepositorio::~CategoriaRepositorio()
{
	PQfinish(conn);
}
