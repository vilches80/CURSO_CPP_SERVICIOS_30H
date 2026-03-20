/*

Lanzar todos los hilos en una coleccion vector 

*/

#include <vector>
#include <algorithm>
#include <thread>
#include <iostream>


class Hilo {

	public:
		void operator()(){
			for (int i = 0 ; i < 3 ; i++){			
				std::cout << "hilo: " << std::this_thread::get_id() << " esta ejecutando " << i << std::endl;
			}
			std::cout << "Termina el hilo: " << std::this_thread::get_id() << std::endl;
		}
};


void test1(){
	std::vector<std::thread> hilos;

	// Creamos 10 hilos y se añaden al vector:
	for (int i = 0 ; i < 5 ; i++){	
		hilos.push_back(std::thread( (Hilo()) ));
		auto &h = hilos.at(i);
		h.join();
	}
}

void test2(){
	std::vector<std::thread> hilos;

	// Creamos 10 hilos y se añaden al vector:
	for (int i = 0 ; i < 10 ; i++)
		hilos.push_back(std::thread( (Hilo()) ));

	// Ahora esperamos a que acaben todos los hilos:
	std::cout << std::endl << "Esperamos por todos los hilos" << std::endl;

	for (auto &h : hilos)
		h.join();

}


int main(){
	test1();
	//test2();
	return 0;
}
