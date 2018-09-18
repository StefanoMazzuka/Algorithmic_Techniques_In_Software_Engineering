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
#include "bintree_eda.h"

using namespace std;

// lee un árbol binario de la entrada estándar
template <typename T>
bintree<T> leerArbol(T vacio) {
	T raiz;
	cin >> raiz;

	if (raiz == vacio) { // es un árbol vacío
		return {};

	}
	else { // leer recursivamente los hijos

		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);

		return { iz, raiz, dr };
	}
}

/*
dado un árbol binario, calcula su altura
el coste es lineal O(n) donde n es el número de nodos del árbol
*/
unsigned int altura(bintree<int> const& arbol) {
	if (arbol.empty()) //caso base si el árbol es vacio
		return 0;
	else
		return 1 + max(altura(arbol.left()), altura(arbol.right()));

	//cogemos el máximo de nodos entre la parte izquierda y derecha del arbol
}

bool esAVL(bintree<int> const& arbol) {

	if (arbol.empty()) return true;

	auto vectorArbol = arbol.inorder();
	int longitud = vectorArbol.size();

	for (int i = 0; i < longitud - 1; i++) {
		if (vectorArbol[i] >= vectorArbol[i + 1]) return false;
	}

	return true;
}

bool esEquilibrado(bintree<int> arbol) {

	if (arbol.empty()) return true;
	else {
		int alt = altura(arbol.right()) - altura(arbol.left());
		if (abs(alt) <= 1 &&
			esEquilibrado(arbol.left()) &&
			esEquilibrado(arbol.right())) return true;
		else return false;
	}
	return false;
}

// COSTE: 
void resuelveCaso() {
	auto arbol = leerArbol(-1);

	if (esEquilibrado(arbol) && esAVL(arbol))
		cout << "SI" << "\n";
	else
		cout << "NO" << "\n";
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
