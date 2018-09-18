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

void equilibrarListas(PriorityQueue<int> &listaPajarosMayores, PriorityQueue<int, greater<int>> &listaPajarosMenores) {
	int diferencia = listaPajarosMayores.size() - listaPajarosMenores.size();
	int edad;
	if (diferencia > 1) {
		edad = listaPajarosMayores.top();
		listaPajarosMayores.pop();
		listaPajarosMenores.push(edad);
	}
	else if (diferencia < 1) {
		edad = listaPajarosMenores.top();
		listaPajarosMenores.pop();
		listaPajarosMayores.push(edad);
	}
}

// COSTE: 
void resuelveCaso(int edad, int numParejas) {
	PriorityQueue<int> listaPajarosMayores;
	PriorityQueue<int, greater<int>> listaPajarosMenores;

	listaPajarosMayores.push(edad);

	for (int i = 0; i < numParejas; i++) {
		for (int i = 0; i < 2; i++) {
			int nuevaEdad;
			cin >> nuevaEdad;
			if (nuevaEdad > listaPajarosMayores.top()) listaPajarosMayores.push(nuevaEdad);
			else listaPajarosMenores.push(nuevaEdad);
		}
		equilibrarListas(listaPajarosMayores, listaPajarosMenores);
		cout << listaPajarosMayores.top() << " ";
	}
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_7.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int edad, numParejas;
	cin >> edad;
	cin >> numParejas;
	while (edad > 0 && numParejas > 0) {
		resuelveCaso(edad, numParejas);
		cin >> edad;
		cin >> numParejas;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}