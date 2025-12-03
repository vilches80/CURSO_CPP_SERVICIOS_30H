#include <crow.h>
//#include <thread.h>
#include <nlohmann/json.hpp>

#include "EmpleadoCROW.h"

using json = nlohmann::json;

EmpleadoCROW::EmpleadoCROW(EmpleadoRepository& repo):repositorio(repo)
{
}

void EmpleadoCROW::run() {
	crow::SimpleApp app;

	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {

		// Recuperamos el objeto json con load para hacer la validacion de la sintaxis:
		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}

		try {

			// Para convertirlo directamente a objeto, utiliza nlohmann:
			json j = json::parse(req.body);
			//if (j.contains("id"))

			// Para convertirlo a objeto:
			Empleado emp = j.get<Empleado>();

			// Insertar en la BD:
			this->repositorio.insertar(emp);

			crow::json::wvalue resul;
			resul["resultado"] = "Se ha creado el empleado correctamente";
			return crow::response(201, resul.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}

		});

	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
		try {
			// Verificar que existe:
			auto empleado = this->repositorio.recuperarEmpleado(id);

			if (!empleado.has_value()) {
				return crow::response(404, "Empleado con id: " + std::to_string(id) + " no existe");
			}

			// Aplica automaticamente la funcion: to_json (de objeto a json)
			json j = *empleado;
			return crow::response(j.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}

		});

	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::GET)([this]() {

		try {
			auto empleados = this->repositorio.listarTodos();
			json j = empleados; // El vector lo pasa a un array de json, y por cada objeto aplica: to_json
			return crow::response(j.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}
		});

	app.multithreaded().concurrency(std::thread::hardware_concurrency()).port(8000).run();
}

EmpleadoCROW::~EmpleadoCROW()
{
}
