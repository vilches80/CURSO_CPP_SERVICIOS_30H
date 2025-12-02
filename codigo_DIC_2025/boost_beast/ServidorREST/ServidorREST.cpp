#include "ServidorREST.h"
// ServidorREST.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

ServidorREST::ServidorREST(net::io_context&, unsigned int port):ioc(ioc), acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {
	this->id = 1;
}

void ServidorREST::run() {
	// Bucle infinito donde estamos aceptando peticiones de los clientes:
	// crear un socket, 
	// acceptar una peticion
	// procesar la peticion

	std::cout << "Servidor REST: escuchando en el puerto " << acceptor.local_endpoint().port() << std::endl;

	for (;;) {
		// Crear el socket:
		tcp::socket socket(ioc);

		// Acceptar una peticion:
		acceptor.accept(socket);

		// procesar la peticion:
		procesarPeticion(socket);
	}
}

void ServidorREST::procesarPeticion(tcp::socket& socket) {
	beast::flat_buffer buffer;
	http::request<http::string_body> request;
	std::string mensaje = "";
	std::string metodo;

	try {
		// Leer la peticion:
		http::read(socket, buffer, request);

		// Extraer el mensaje y la querystring
		std::string target = request.target();
		metodo = request.method_string();

		std::cout << "Peticion: " << target << " metodo: " << metodo << std::endl;

		auto pos = target.find("?msg=");

		if (pos != std::string::npos) {
			mensaje = target.substr(pos + 5);
		}

		// Respuesta al cliente:
		http::response<http::string_body> response{ http::status::ok, request.version() };
		response.set(http::field::server, "Beast/1.0");
		response.set(http::field::content_type, "text/plain");
		response.body() = "Respuesta del servidor: " + mensaje;

		// Escribir respuesta:
		http::write(socket, response);
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
}


std::string ServidorREST::peticionGET()
{
	return std::string();
}

std::string ServidorREST::peticionPOST(const std::string&)
{
	return std::string();
}

std::string ServidorREST::peticionDELETE(int)
{
	return std::string();
}

ServidorREST::~ServidorREST()
{
}
