#pragma once
#include  <libpq-fe.h>
#include <optional>
#include <vector>
#include <string>
#include "Categoria.h"

class CategoriaRepositorio
{
public:
	CategoriaRepositorio(std::string cadconex);
	std::optional<Categoria> read(int id);
	int create(const Categoria& categoria);
	int update(const Categoria& categoria);
	int deleteid(int id);
	std::vector<Categoria> selectAll();
	~CategoriaRepositorio();

private:
	PGconn* conn;
};

