#include "ServicioCrow.h"

#define PORT 8000

ServicioCrow::ServicioCrow()
{
	// Inicializar el indice de la coleccion:
	this->siguiente_id = 1;
}

void ServicioCrow::run() {
	crow::SimpleApp app;

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
		
		// Recoger el usuario del cuerpo de la peticion:
		auto body = crow::json::load(req.body);

		// Si vienen errores de sintaxis, devuelve objeto vacio:
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}

		// Dar de alta el nuevo usuario:
		std::lock_guard<std::mutex> lock(this->mutex);
		int id = this->siguiente_id++;
		this->usuarios[id] = body;

		// Montar las respuesta para el cliente:
		crow::json::wvalue res;
		res["id"] = id;
		res["mensaje"] = "usuario";

		return crow::response(201, res);
	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {

		std::lock_guard<std::mutex> lock(this->mutex);
		int n = this->usuarios.count(id);

		if (!n) {
			// Si no existe -> recurso no disponible
			return crow::response(404, "Usuario " + std::to_string(id) + " no encontrado");
		}

		// Montar las respuesta para el cliente:
		crow::json::wvalue res;

		// Recuperar el usuario con la clave id
		crow::json::rvalue user = usuarios[id];

		res["id"] = id;
		res["nombre"] = user["nombre"].s(); // como string
		res["email"] = user["email"].s();

		return crow::response(res); // Si no ponemos código, se entiende 200

		});

	// Poner en marcha el servicio:
	app.port(PORT).multithreaded().concurrency(4).run();
}

ServicioCrow::~ServicioCrow()
{
}
