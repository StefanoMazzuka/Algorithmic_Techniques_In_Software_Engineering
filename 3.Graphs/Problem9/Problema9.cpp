/*
GRUPO:
TAIS

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include<vector>
#include"Grafo.h"

using namespace std;

void dfs(Grafo const& G, size_t v, vector<bool> &marcados, int &tamGrupo) {
	++tamGrupo;
	marcados[v] = true; // para no repetir vértices
	for (auto w : G.adj(v)) { // recorremos todos los adyacentes a v
		if (!marcados[w]) {
			dfs(G, w, marcados, tamGrupo);
		}
	}
}

// COSTE:
void resuelveCaso() {

	int N, M;
	cin >> N;
	cin >> M;

	Grafo grafo(N);
	
	// Leemos el grafo
	int verticeA, verticeB;
	for (int i = 0; i < M; i++) {
		cin >> verticeA;
		cin >> verticeB;
		grafo.ponArista(verticeA - 1, verticeB - 1);
	}
	
	int grupoMayor = 0, tamGrupo;
	vector<bool> marcados(N, false);

	for (int i = 0; i < N; i++) {
		tamGrupo = 0;
		dfs(grafo, i, marcados, tamGrupo);
		if (tamGrupo > grupoMayor) grupoMayor = tamGrupo;
	}

	cout << grupoMayor << endl;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_9.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int casos;
	cin >> casos;
	while (casos > 0) {
		resuelveCaso();
		--casos;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}