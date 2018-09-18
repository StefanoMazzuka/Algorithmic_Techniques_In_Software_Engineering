/*
GRUPO:
TAIS 26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include"Matriz.h"
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

typedef struct
{
	int longitud;
	int coste;
}tCuerda;

// COSTE: O(N + n*logn) Siendo N el num de peliculas
bool resuelveCaso() {

	int N, L;

	cin >> N >> L;

	if (!cin) return false;

	tCuerda cuerda;
	vector<tCuerda> cuerdas;
	for (int i = 0; i < N; i++) {
		cin >> cuerda.longitud >> cuerda.coste;
		cuerdas[i] = cuerda;
	}

	Matriz<int> numManeras(N + 1, N + 1, 0);
	int inicio = 1;

	for (int i = 0; i < N; i++) {
		for (int j = inicio; j < N; j++) {
			int acumulado = cuerdas[inicio + 1].longitud;
			cuerdas[j] 
		}
		inicio++;
	}

	return true;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_27.txt");
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