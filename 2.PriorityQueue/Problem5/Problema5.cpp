/*
GRUPO:
TAIS26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include"PriorityQueue.h"

using namespace std;

// COSTE: 
long long resuelveCaso(int numEquipos) {
	PriorityQueue<long long> listaEquipos;
	long long numSeguidores, numGorras = 0;

	// Metemos los seguidores en una pila
	for (int i = 0; i < numEquipos; i++) {
		cin >> numSeguidores;
		listaEquipos.push(numSeguidores);
	}

	long long equipoA, equipoB;
	for (int i = 0; i < numEquipos - 1; i++) {
		equipoA = listaEquipos.top();
		listaEquipos.pop();
		equipoB = listaEquipos.top();
		listaEquipos.pop();
		numGorras += (equipoA + equipoB);
		listaEquipos.push(equipoA + equipoB);
	}

	return numGorras;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_5.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int numEquipos;
	cin >> numEquipos;
	while (numEquipos > 0) {
		cout << resuelveCaso(numEquipos) << endl;
		cin >> numEquipos;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}