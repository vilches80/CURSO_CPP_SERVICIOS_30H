// punteros.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <memory>

#include "Vector.h"

void testC() {
    int n = 10;
    int* ptr = nullptr;
    int* ptr2 = nullptr;

    ptr = (int*)std::malloc(sizeof(int) * n); // Bloque completo en bytes
    ptr2 = (int*)std::calloc(n, sizeof(int)); // numero de elementos * ocupan, inicializa a cero los elementos

    // Realloc, ampliar un bloque de memoria:
    // Ampliar m elementos:
    int m = 5;

    ptr = (int*)std::realloc(ptr, (static_cast<unsigned long long>(n) + m) * sizeof(int)); // puntero original y tamaño total final.

    free(ptr);
    free(ptr2);
}

void testSP() {
    auto a_ptr = std::unique_ptr<int>(new int);
    //auto b_ptr = a_ptr; //No te deja hacer la copia!
}

int main()
{
    Vector v1;

    v1.add(1);
    v1.add(2);
    v1.add(3);
    v1.add(41);

    v1.imprimir();

    Vector v2(v1);
    v2.imprimir();

    Vector v3;
    v3 = v1;
    v3.imprimir();


    return 0;
}
