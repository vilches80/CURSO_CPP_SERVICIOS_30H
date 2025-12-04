// ServidorgRPC.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "saludo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using saludo::Saludo;
using saludo::Solicitud;
using saludo::Respuesta;


// Crear una clase que herede de Saludo::Service
class SaludoServiceImpl final : public Saludo::Service {

	Status DiHola(ServerContext* context, const Solicitud* request, Respuesta* reply) override {
		std::string nombre = request->nombre();
		reply->set_mensaje("Hola " + nombre);
		return Status::OK;
	}
};

void ejecutarServidor() {
	std::string direccion = "0.0.0.0:50051";
	SaludoServiceImpl servicio;

	ServerBuilder builder;

	// Indicar la direccion y el puerto donde se despliega el servidor
	builder.AddListeningPort(direccion, grpc::InsecureServerCredentials());

	// Registrar el servicio:
	builder.RegisterService(&servicio);

	// Poner en marcha el servidor:
	std::unique_ptr<Server> server(builder.BuildAndStart());

	std::cout << "Servidor escuchando en " << direccion << std::endl;
	server->Wait();
}


int main()
{
	ejecutarServidor();
	return 0;
}
