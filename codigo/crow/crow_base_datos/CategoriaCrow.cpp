#include <crow.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include "Categoria.h"
#include "CategoriaCrow.h"

using json = nlohmann::json;


CategoriaCrow::CategoriaCrow(const CategoriaRepositorio& repo):repo(repo)
{
}

void CategoriaCrow::run()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/categorias/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
		
		try {
			auto cat = this->repo.read(id);
			if (cat) {
				// cat es un ptr a una estructura
				json j = *cat;

				// Convertir el json a string con dump
				return crow::response(200, j.dump(4));
			}
			else {
				// No existe.
				return crow::response(404, "Categoria con el id: " + std::to_string(id) + " no existe");
			}
		}
		catch (const std::exception& e) {
			std::string msg = e.what();
			return crow::response(500, "Error interno en el servidor: " + msg);
		}
	});

	CROW_ROUTE(app, "/categorias").methods(crow::HTTPMethod::GET)([this]() {
		
		try {
			auto categorias = this->repo.selectAll();			
			json j = categorias;

			// Convertir el json a string con dump
			return crow::response(200, j.dump(4));
		}
		catch (const std::exception& e) {
			std::string msg = e.what();
			return crow::response(500, "Error interno en el servidor: " + msg);
		}
	});

	CROW_ROUTE(app, "/categorias").methods(crow::HTTPMethod::PUT)([this](const crow::request& req) {

		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}
	
		try {
			// Para convertir directamente a la estructura:
			json j = json::parse(req.body);

			// Conversion: funcion from_json()
			Categoria c = j.get<Categoria>();

			int filas = this->repo.update(c);
			if (filas == 0) {
				return crow::response(404, "Categoria con el id: " + std::to_string(c.id) + " no existe");
			}
			else {
				return crow::response(204);
			}
		} 
		catch (const std::exception& e) {
				std::string msg = e.what();
				return crow::response(500, "Error interno en el servidor: " + msg);
		}

	});

	CROW_ROUTE(app, "/categorias/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {
		
		try {
			int filas = this->repo.deleteid(id);
			if (filas == 0) {
				return crow::response(404, "Categoria con el id: " + std::to_string(id) + " no existe");
			}
			else {
				return crow::response(204);
			}

		}
		catch (const std::exception& e) {
				std::string msg = e.what();
				return crow::response(500, "Error interno en el servidor: " + msg);
		}
		
	});

	// Puesta en marcha del servidor
	app.port(8080).concurrency(std::thread::hardware_concurrency()).multithreaded().run();
}

CategoriaCrow::~CategoriaCrow()
{
}
