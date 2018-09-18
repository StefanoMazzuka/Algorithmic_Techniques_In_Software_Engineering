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
#include"PriorityQueue.h"

using namespace std;

struct grupoDeInstrumentos {
	int numInstrumentos;
	int numPartituras;
	int grupoMayor;
	bool operator<(const grupoDeInstrumentos &otro) const {
		return otro.grupoMayor < grupoMayor;
	}
};

grupoDeInstrumentos actualizarGrupoMayor(grupoDeInstrumentos grupo) {
	grupo.grupoMayor = (grupo.numInstrumentos / grupo.numPartituras);
	if ((grupo.numInstrumentos % grupo.numPartituras) != 0) grupo.grupoMayor++;

	return grupo;
}

// COSTE: O(N) siendo N el número de partituras.
bool resuelveCaso() {

	int p, n;
	cin >> p;
	cin >> n;

	if (!cin) return false;

	PriorityQueue<grupoDeInstrumentos> listaGrupos;
	grupoDeInstrumentos grupo;

	// Meto los datos en la cola
	for (int i = 0; i < n; i++) {
		cin >> grupo.numInstrumentos;
		grupo.numPartituras = 1;
		grupo = actualizarGrupoMayor(grupo);
		p--;
		listaGrupos.push(grupo);
	}

	grupo = listaGrupos.top();
	listaGrupos.pop();

	if (listaGrupos.empty()) {
		grupo.numPartituras += p;
		grupo = actualizarGrupoMayor(grupo);
	}

	else {
		for (int i = 0; i < p; i++) {

			grupo.numPartituras++;
			grupo = actualizarGrupoMayor(grupo);

			if (grupo.grupoMayor < listaGrupos.top().grupoMayor) {
				listaGrupos.push(grupo);
				grupo = listaGrupos.top();
				listaGrupos.pop();
			}
		}
	}

	cout << grupo.grupoMayor << endl;

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