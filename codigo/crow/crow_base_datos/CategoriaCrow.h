#pragma once

#include <string>
#include "CategoriaRepositorio.h"

class CategoriaCrow
{
public:
	CategoriaCrow(const CategoriaRepositorio& repo);
	void run();
	~CategoriaCrow();

private:
	CategoriaRepositorio repo;
};

