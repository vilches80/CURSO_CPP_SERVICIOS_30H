#include "EmpleadoRepositorio.h"

EmpleadoRepositorio::EmpleadoRepositorio(soci::session&sql):sql(sql)
{
}

std::optional<Empleado> EmpleadoRepositorio::read(int id)
{
	try {
		Empleado emp;
		soci::indicator ind;

		sql << "select id, nombre, cargo from empleados where id = :id",
			soci::use(id), soci::into(emp.id, ind), soci::into(emp.nombre), soci::into(emp.cargo);

		if (ind == soci::i_null) {
			// No ha encontrado el empleado:
			return std::nullopt;
		}

		return emp;
	}
	catch (const std::exception& e) {
		throw e;
	}
}

bool EmpleadoRepositorio::create(const Empleado& emp)
{
	sql << "insert into empleados(id, nombre, cargo) values(:id, :nombre, :cargo)",
		soci::use(emp.id), soci::use(emp.nombre), soci::use(emp.cargo);
	//std::size_t filas = sql.get_affected_rows();
	return true;
}

bool EmpleadoRepositorio::update(const Empleado& emp)
{
	sql << "update empleados set nombre=:nombre, cargo=:cargo where id=:id",
		soci::use(emp.nombre), soci::use(emp.cargo), soci::use(emp.id);
	return true;
}

bool EmpleadoRepositorio::delete_(int id)
{
	sql << "delete from empleados where id=:id", soci::use(id);
	return true;
}

std::vector<Empleado> EmpleadoRepositorio::select()
{
	std::vector<Empleado> empleados;

	soci::rowset<soci::row> rs = sql.prepare << "select id, nombre, cargo from empleados";

	for (const auto& r : rs) {
		Empleado emp;
		emp.id = r.get<int>(0);
		emp.nombre = r.get<std::string>(1);
		emp.cargo = r.get<std::string>(2);
		empleados.push_back(emp);
	}

	return empleados;
}
