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
#include "Petroleros.h"

using Mapa = std::vector<std::string>;

/*
COSTE:
*/

// resolvemos cada caso de prueba
bool resuelveCaso() {

	//leemos los datos y no sigue si no hay datos que leer
	size_t columnas, filas, i = 0;
	std::cin >> filas;

	if (!std::cin)
		return false;

	std::cin >> columnas;

	std::cin.ignore(1);
	Mapa mapa(filas);

	while (i < filas){
		getline(std::cin, mapa[i]);
		i++;
	}

	int celdasContaminadas, nFila, nColumna, cnt = 0;
	std::cin >> celdasContaminadas;

	Petroleros p(mapa,filas,columnas);
	std::cout << p.contaminacionMayor() << " ";

	while (celdasContaminadas != 0){

		std::cin >> nFila;
		std::cin >> nColumna;
		//pasamos la nueva fila yy columna con lamancha y la unimos al resto de manchas si es posible
		//restamos 1 porque empezamos desde 0
		p.unirMancha(nFila - 1, nColumna - 1);		

		std::cout << p.contaminacionMayor() << " ";
		celdasContaminadas--;
	}

	std::cout << "\n";

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