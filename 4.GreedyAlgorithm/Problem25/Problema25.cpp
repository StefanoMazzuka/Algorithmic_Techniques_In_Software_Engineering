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

struct tConferencia
{
	int horaInicio;
	int horaFin;
	bool operator<(const tConferencia& conferenciaDos) const {
		return horaInicio < conferenciaDos.horaInicio;
	}
};

// COSTE: O(N) Siendo N el num de conferencias.
void resuelveCaso(int N) {

	tConferencia conferencia;
	PriorityQueue<tConferencia> conferencias;

	// Leemos las conferencias
	for (int i = 0; i < N; i++) {
		cin >> conferencia.horaInicio >> conferencia.horaFin;
		conferencias.push(conferencia);
	}

	PriorityQueue<int> salas;
	salas.push(0); // Metemos un 0 a la pila para que pueda empezar a comparar
	for (int i = 0; i < N; i++) {
		if (conferencias.top().horaInicio >= salas.top()) {
			salas.pop();
			salas.push(conferencias.top().horaFin);
		}
		else salas.push(conferencias.top().horaFin);
		conferencias.pop();
	}

	cout << salas.size() << endl;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_25.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int N;
	cin >> N;
	while (N != 0) {
		resuelveCaso(N);
		cin >> N;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}