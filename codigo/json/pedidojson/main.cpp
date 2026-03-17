// pedidojson.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <sstream>

void testLibreria() {
	nlohmann::json doc;
	doc["curso"] = "Microservicios en C++";
	doc["horas"] = 25;
	doc["tecnologias"] = { "xml", "json", "rest", "soap" };
	std::cout << "Json: " << doc.dump(4) << std::endl;
	std::cout << "curso: " << doc["curso"] << std::endl;
}

void testPedidos() {
	std::string s = "10248;WILMK;Federal Shipping;Buchanan;32.38;Finlandia";
}

int main()
{
	testLibreria();
	// testPedidos();
	return 0;
	
}

