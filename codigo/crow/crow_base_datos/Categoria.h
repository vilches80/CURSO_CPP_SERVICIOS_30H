#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Categoria {
	int id;
	std::string nombre;
};

// Conversion a JSON:
void to_json(json& j, const Categoria& c) {
	j = json{
		{"id", c.id},
		{"nombre", c.nombre}
	};
}

// Conversion a Categoria:
void from_json(const json& j, Categoria& c) {
	j.at("id").get_to(c.id);
	j.at("nombre").get_to(c.nombre);
}
