/*
GRUPO:
TAIS

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include<math.h>
#include"bintree_eda.h"

using namespace std;

// Lee un árbol binario de la entrada estándar
bintree<char> leerArbol(char vacio) {
	char raiz;
	cin >> raiz;
	if (raiz == vacio) return{}; // es un árbol vacío 
	else { // leer recursivamente los hijos
		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);
		return{ iz, raiz, dr };
	}
}

// Dado un árbol binario, calcula su altura
// Lineal en el número N de nodos del árbol, O(N)
unsigned int altura(bintree<char> const& arbol) {
	if (arbol.empty())
		return 0;
	else
		return 1 + max(altura(arbol.left()), altura(arbol.right()));
}

// COSTE: 
bool esEquilibrado(bintree<char> arbol) {

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

void resuelveCaso() {
	bintree<char> arbol;
	char punto = '.';
	arbol = leerArbol(punto);

	if (esEquilibrado(arbol)) cout << "SI" << endl;
	else cout << "NO" << endl;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_1.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}