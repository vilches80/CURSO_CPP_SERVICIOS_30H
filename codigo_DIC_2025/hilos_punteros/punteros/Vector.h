#pragma once
class Vector
{
private:
	int* numeros;
	int n;
	int ocupacion; // indica el nro. de elementos ocupados

public:
	Vector(int = 10);

	// Constructor copia:
	//Vector(const Vector&) = delete; // Para eliminarlos!
	
	// Operador =
	//Vector& operator=(const Vector&) = delete; // Para eliminar

	Vector(const Vector&);
	Vector& operator=(const Vector&);

	bool add(int);
	void imprimir();
	~Vector();
};