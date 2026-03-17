// pedidojson.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <sstream>
#include <fstream>
#include <vector>

#include "Pedido.h"
#include "Utilidades.h"

void testLibreria() {
	nlohmann::json doc;
	doc["curso"] = "Microservicios en C++";
	doc["horas"] = 25;
	doc["tecnologias"] = { "xml", "json", "rest", "soap" };
	std::cout << "Json: " << std::endl << doc.dump(4) << std::endl;
	std::cout << "curso: " << doc["curso"] << std::endl;

	/////////////////////////////

	std::istringstream ss(R"({"nombre":"Ana","edad":28,"intereses":["programacion","musica","senderismo"]})");
	nlohmann::json doc2;
	// Se convierte a json:
	ss >> doc2;
	std::cout << "nombre: " << doc2["nombre"] << std::endl << std::endl;
	std::cout << doc2.dump(4) << std::endl;
}

void testPedidos() {
	std::string s = "10248;WILMK;Federal Shipping;Buchanan;32.38;Finlandia";
	Pedido p(s);

	nlohmann::json doc = p.to_json();
	std::cout << doc.dump(4) << std::endl;
}

void testFicheroCSV_Json() {
	std::string ficheroCSV = "pedidos.csv";
	std::string ficheroJSON = "pedidos.json";

	std::ifstream fin(ficheroCSV);
	std::ofstream fout(ficheroJSON);

	std::string linea;
	std::vector<std::string> campos;
	bool cabs = true;
	std::vector<nlohmann::json> array;
	nlohmann::json documento;

	if (!fin) {
		std::cerr << "No se ha encontrado el fichero: " << ficheroCSV << std::endl;
		return;
	}

	while (std::getline(fin, linea)) {
		//std::cout << linea << std::endl;

		if (cabs) {
			cabs = false;

		}
		else {
			Utilidades::split(linea, ';', campos);
			Pedido p(linea);
			array.push_back(p.to_json());
			campos.clear();
		}
	}

	// Convertir el array de pedidos a un documento de Json;
	documento = array;

	// Imprimir en consola:
	std::cout << documento.dump(4) << std::endl;

	// Imprimir a un fichero: json
	fout << documento.dump(4) << std::endl;
	
	fout.close();
	fin.close();

}


int main()
{
	//testLibreria();
	//testPedidos();
	testFicheroCSV_Json();
	return 0;
	
}

