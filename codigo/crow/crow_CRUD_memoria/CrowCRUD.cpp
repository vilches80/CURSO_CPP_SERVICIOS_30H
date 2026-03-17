#include "CrowCRUD.h"

CrowCRUD::CrowCRUD()
{
	// Inicializar la clave:
	this->siguiente_id = 1;
}

void CrowCRUD::run()
{
	crow::SimpleApp app; 

	// Create - POST /usuarios
	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {

		// Recoger el json que viene de la Request: el tipo es: crow::json::rvalue
		auto body = crow::json::load(req.body);
		if (!body) {
			// 400 Bad Request, el json no coincide con el json esperado:
			return crow::response(400, "Json incorrecto");
		}

		// Guardar el json enviado en el mapa: lo tenemos que hacer en  exclusión mutua;
		std::lock_guard<std::mutex> lock(mtx);
		int id = this->siguiente_id++;
		this->usuarios[id] = std::move(body); // ojo si copiamos no funciona bien, no se ven bien los datos.

		// Montamos la respuesta:
		crow::json::wvalue resp;
		resp["id"] = id;

		// 201: éxito, para peticiones post
		return crow::response(201, resp);
	});

	// Get - GET /usuarios
	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {

		std::lock_guard<std::mutex> lock(this->mtx);

		// Definimos una estructura lista que se convierte a un array de json
		crow::json::wvalue lista = crow::json::wvalue::list();
		int i = 0;
		
		for (const auto& [id, usuario] : this->usuarios) {
			crow::json::wvalue item;
			item["id"] = id;

			if (usuario.has("nombre"))
				item["nombre"] = usuario["nombre"].s();
			else
				item["nombre"] = "";

			item["edad"] = usuario["edad"].i();

			// Cargar en la lista:
			lista[i++] = std::move(item);
		}

		// Definir la respuesta:
		crow::json::wvalue  resp;
		resp["usuarios"] = std::move(lista);
		return crow::response(resp);
	});

	app.port(8080).multithreaded().run();
}

CrowCRUD::~CrowCRUD()
{
}
