/*
GRUPO:
TAIS

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include"PriorityQueue.h"

using namespace std;

// COSTE: O(N) Siendo N el num de agujeros.
bool resuelveCaso() {

	int N, L;
	cin >> N >> L;

	if (!cin) return false;

	PriorityQueue<int> agujeros;

	for (int i = 0; i < N; i++) {
		int pos;
		cin >> pos;
		agujeros.push(pos);
	}

	int numParches = 1, posInicial = agujeros.top();
	agujeros.pop();

	for (int i = 1; i < N; i++) {
		if (agujeros.top() - posInicial <= L) {
			agujeros.pop();
		}
		else {
			numParches++;
			posInicial = agujeros.top();
			agujeros.pop();
		}
	}

	cout << numParches << endl;

	return true;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso()) {}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}