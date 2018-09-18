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
#include "FreeLove.h"

using Mapa = std::vector<std::string>;

/*
	COSTE: O(n) siendo n el numero de filas
	colocar cada sensor en O(k*4) sinedo k 
	el numero de sensores a colocar por las 4 direcciones
	recorrido en anchura O(n)
*/

// resolvemos cada caso de prueba
void resuelveCaso() {

	//leemos los datos y no sigue si no hay datos que leer
	size_t columnas, filas, i = 0;
	std::cin >> columnas;
	std::cin >> filas;
		
	std::cin.ignore(1);
	Mapa mapa(filas);

	while (i < filas){
		getline(cin, mapa[i]);
		i++;
	}

	FreeLove fl(mapa);

	if (fl.minimo() > 0)
		std::cout << fl.minimo() << "\n";
	else
		std::cout << "NO \n";
}//metodo


int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int casos;
	std::cin >> casos;

	while (casos != 0){
		resuelveCaso();
		casos--;
	}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}