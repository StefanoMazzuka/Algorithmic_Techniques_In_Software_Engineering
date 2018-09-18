/*
GRUPO:
TAIS 26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include"PriorityQueue.h"

using namespace std;

// COSTE: O(N) Siendo N el num de ciudades.
bool resuelveCaso() {

	int N;

	cin >> N;

	if (!cin) return false;

	PriorityQueue<int, greater<int>> enemigos;
	PriorityQueue<int, greater<int>> defensa;

	int numEfectivos;
	for (int i = 0; i < N; i++) {
		cin >> numEfectivos;
		enemigos.push(numEfectivos);
	}

	for (int i = 0; i < N; i++) {
		cin >> numEfectivos;
		defensa.push(numEfectivos);
	}

	int numVictorias = 0;
	for (int i = 0; i < N; i++) {
		if (defensa.top() >= enemigos.top()) {
			defensa.pop();
			enemigos.pop();
			numVictorias++;
		}

		else enemigos.pop();
	}

	cout << numVictorias << endl;

	return true;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_23.txt");
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