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
#include "OvejaNegra.h"

using Mapa = std::vector<std::string>;

/*
	COSTE: O(M) siedno M = (filas * columnas - (numero de puntos negros))
	cada punto blanco recorre todos sus adyacentes si no están marcados
	por lo que se recorren si o si todas las casillas (menos X)
*/

// resolvemos cada caso de prueba
bool resuelveCaso() {

	//leemos los datos y no sigue si no hay datos que leer
	size_t columnas, filas, i = 0;
	std::cin >> columnas;
		
	if (!std::cin)
		return false;

	std::cin >> filas;

	std::cin.ignore(1);
	Mapa mapa(filas);

	while (i < filas){
		getline(std::cin, mapa[i]);
		i++;
	}

	OvejaNegra on(mapa);

	std::cout << on.ovejasBlancas() << "\n";

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