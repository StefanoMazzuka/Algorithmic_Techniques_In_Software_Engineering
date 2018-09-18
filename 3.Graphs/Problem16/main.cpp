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
#include "CaminoCole.h"

/*
	COSTE: O(E*logV)
	siendo E el numero de aristas y V el numero de vertices
	las aristas la comprobamso todas pero no tenemso porque llegar a
	todos los veertices
*/
bool resuelveCaso() {
	
	size_t vertices, aristas, aristaAux;
	std::cin >> vertices;
	std::cin >> aristas;
	aristaAux = aristas;

	if (!std::cin)
		return false;

	//grafoValorado
	GrafoValorado<int> gv(vertices);
	CaminoCole bc(gv, aristas);

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
	int inicio = 0;
	if (aristaAux != 0)
		bc.recorrerGrafo(inicio);
	
	if (vertices == 1)
		std::cout << 1 << "\n";
	else
		std::cout << bc.caminoMinimo() << "\n";

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