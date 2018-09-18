/*
	Grupo TAIS26 Silvia y Stefano

	solución al problema 03 donde indicamos 
	 el rango de valor del arbol entre k1 y k2
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include "TreeMap_AVL.h"


// lee un árbol binario de la entrada estándar
map<int, int>insertaEnArbol(int* v, int n){

	map<int, int> arbol;

	for (int i = 0; i < n; i++){
		arbol.insert(v[i]);
	}
		 

	return arbol;
}

void resuelveCaso(int nodos) {
	
	int* v = new int[nodos];

	for (int i = 0; i <nodos; i++){
		std::cin >> v[i];
	}

	auto arbol = insertaEnArbol(v,nodos);
	
	int puntos[2];
	std::cin >> puntos[0];
	std::cin >> puntos[1];
	
	arbol.rango(arbol,puntos[0],puntos[1]);

}

int main() {

// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
		std::ifstream in("casos.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	int tam;
	std::cin >> tam;

	while (tam != 0){
		resuelveCaso(tam);
		std::cin >> tam;
	}

	// para dejar todo como estaba al principio
	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		system("PAUSE");
	#endif

		return 0;
}