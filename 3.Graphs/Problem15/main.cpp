/*
GRUPO:
TAIS26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "BarroCity.h"

/*
	COSTE: O(n) siendo n el numero de vertices del grafo
	O(n) porque recorremos todos los vertices para sumar el coste de cada uno
	O(n) recorremos cada vertice y sus adyacentes
*/
bool resuelveCaso() {
	
	size_t vertices, aristas;
	std::cin >> vertices;
	std::cin >> aristas;


	if (!std::cin)
		return false;

	//grafoValorado
	GrafoValorado<int> gv(vertices);
	BarroCity bc(gv, aristas);

	int vOrigen, vDestino, coste;

	while (aristas != 0){

		std::cin >> vOrigen;
		std::cin >> vDestino;
		std::cin >> coste;

		//colocamos cada arista nueva (restamos 1 para que empiece en 0)
		bc.colocarArista(vOrigen-1, vDestino-1, coste);

		aristas--;
	}

	//empezamos a recorrer el grafo desde el vertice 0
	bc.recorrerGrafo();
	
	//nos devuelve el camino con menor coste  pasando por todos los vertices sin ciclos
	int m = bc.caminoMinimo();

	if (m != 0)
		std::cout << m << "\n";
	else
		std::cout << "Imposible \n";

	return true;

}//metodo


int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}