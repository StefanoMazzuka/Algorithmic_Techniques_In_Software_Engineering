/*
	Grupo TAIS26 Silvia y Stefano

	solución al problema 00 donde obtenemso la altura de un arbol
	de manera recursiva
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

// lee un árbol binario de la entrada estándar
template <typename T>
bintree<T> leerArbol(T vacio) {
	T raiz;
	std::cin >> raiz;

	if (raiz == vacio) { // es un árbol vacío
		return {};

	} else { // leer recursivamente los hijos

		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);

		return {iz, raiz, dr};
	}
}

/*
	dado un árbol binario, calcula su altura
	el coste es lineal O(n) donde n es el número de nodos del árbol
*/
unsigned int altura(bintree<char> const& arbol) {
	if (arbol.empty()) //caso base si el árbol es vacio
		return 0;
	else
		return 1 + max(altura(arbol.left()), altura(arbol.right()));

	//cogemos el maximo de nodos entre la parte izquierda y derecha del arbol
}

// resolvemos cada caso de prueba
void resuelveCaso() {
	auto arbol = leerArbol('.');
	int sol = altura(arbol);
	std::cout << sol << "\n";
}

int main() {

// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
		std::ifstream in("casos_0.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	int numCasos;
	std::cin >> numCasos;

	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		system("PAUSE");
	#endif

	return 0;
}
