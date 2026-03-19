#include <stdexcept>

#include "CategoriaRepositorio.h"

CategoriaRepositorio::CategoriaRepositorio(PGconn* conn):conn(conn)
{
}

std::optional<Categoria> CategoriaRepositorio::read(int id)
{
	return std::optional<Categoria>();
}

void CategoriaRepositorio::create(const Categoria& categoria)
{
}

void CategoriaRepositorio::update(const Categoria& categoria)
{
}

void CategoriaRepositorio::deleteid(int id)
{
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
}
