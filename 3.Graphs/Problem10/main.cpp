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
#include "Grafo.h"
#include "Bipartito.h"

/*
	COSTE: O(n) sinedo n el numero de aristas
	resolvemos cada caso de prueba
*/
bool resuelveCaso() {

	//leemos los datos y no sigue si no hay datos que leer
	int vertices, aristas;
	std::cin >> vertices;
	std::cin >> aristas;

	if (!std::cin) return false;

	Grafo grafo = Grafo(vertices);

	while (aristas != 0){

		int v1, v2;
		std::cin >> v1;
		std::cin >> v2;

		grafo.ponArista(v1, v2); //añadimos dos vertices al grafo con una arista

		aristas--;
	}
	
	/*
		creamos un grafo de la clase Bipartito que nos dirá directamente si es o no Bipartito
	*/
	Bipartito gb(grafo, grafo.V());
	
	if (gb.GrafoBipartito())
		std::cout << "SI\n";
	else
		std::cout << "NO\n";
	
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