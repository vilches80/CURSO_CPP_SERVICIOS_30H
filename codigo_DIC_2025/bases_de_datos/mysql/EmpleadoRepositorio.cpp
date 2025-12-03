#include "EmpleadoRepositorio.h"

EmpleadoRepositorio::EmpleadoRepositorio(soci::session&sql):sql(sql)
{
}

std::optional<Empleado> EmpleadoRepositorio::read(int id)
{
	Empleado emp;
	soci::indicator ind;

	sql << "select id, nombre, cargo from empleado where id = :id",
		soci::use(id), soci::into(emp.id, ind), soci::into(emp.nombre), soci::into(emp.cargo);

	if (ind == soci::i_null) {
		// No ha encontrado el empleado:
		return std::nullopt;
	}

	return emp;
}

bool EmpleadoRepositorio::create(const Empleado&)
{
	return false;
}

bool EmpleadoRepositorio::update(const Empleado&)
{
	return false;
}

bool EmpleadoRepositorio::delete_(int)
{
	return false;
}

std::vector<Empleado> EmpleadoRepositorio::select()
{
	return std::vector<Empleado>();
}
