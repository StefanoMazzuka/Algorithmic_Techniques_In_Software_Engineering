/*
	Grupo TAIS26 Silvia y Stefano

	solución al problema 04 donde indicamos 
	 el ndo que ocupa la posicion que pasamos
	 si no la encuetnra mostrará ??
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include "TreeMap_AVL.h"


// lee un árbol binario de la entrada estándar
map<int, int>insertaEnArbol(int* v, int n){

	map<int, int> arbol;
	int pos = 1;

	for (int i = 0; i < n; i++){
		arbol.insert(v[i],pos);
		pos++;
	}

	return arbol;
}


void resuelveCaso(int nodos) {
	
	int* v = new int[nodos];

	for (int i = 0; i <nodos; i++){
		std::cin >> v[i];
	}

	//insertamso de manera que se equilibre
	auto arbol = insertaEnArbol(v,nodos);
	
	int numPosiciones;
	std::cin >> numPosiciones;

	int* VectorPosicionesABuscar = new int[numPosiciones];
	for (int i = 0; i <numPosiciones; i++){
		std::cin >> VectorPosicionesABuscar[i];
	}

	arbol.KesimioElemento(arbol,numPosiciones,VectorPosicionesABuscar);

}

int main() {

// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
		std::ifstream in("casos4.txt");
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