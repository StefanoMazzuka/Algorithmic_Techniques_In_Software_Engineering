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

const int INF = 1000000000;

typedef struct
{
	int longitud;
	int coste;
}tCuerda;

/*

costeMin(i, j) donde tengo cuerdas desde 0...i y tengo que conseguir j como longitud.
costeMin(i, j) = coste(i - 1, j) si i > j.
costeMin(i, j) = min[costeMin(i - 1, j), costeMin(i - 1, j - cuerdas[i].longitud) + cuerdas[i].coste] si i <= j.
costeMin(0, j) = INF
costeMin(i, 0) = 0

*/

// Forma recursiva
/*
int formasDos(vector<tCuerda> const& cuerdas, int i, int j) {
	if (j == 0) return 1;
	if (i == 0) return 0;

	return formasDos(cuerdas, i - 1, j - cuerdas[i].longitud) + formasDos(cuerdas, i - 1, j);
}
*/

bool posible(vector<tCuerda> const cuerdas, int L) {

	size_t n = cuerdas.size() - 1;
	Matriz<bool> posibles(n + 1, L + 1, false);

	// Rellenar la matriz
	posibles[0][0] = true;
	for (int i = 1; i <= n; ++i) {
		posibles[i][0] = true;
		for (int j = 1; j <= L; ++j) {
			if (cuerdas[i].longitud > j)
				posibles[i][j] = posibles[i - 1][j];
			else
				posibles[i][j] = (posibles[i - 1][j] || posibles[i - 1][j - cuerdas[i].longitud]);
		}
	}

	return posibles[n][L];
}
long long int costeMin(vector<tCuerda> const cuerdas, int L) {

	size_t n = cuerdas.size() - 1;
	Matriz<long long int> costes(n + 1, L + 1, INF);

	// Rellenar la matriz
	costes[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		costes[i][0] = 0;
		for (int j = 1; j <= L; ++j) {
			if (cuerdas[i].longitud > j)
				costes[i][j] = costes[i - 1][j];
			else
				costes[i][j] = min(costes[i - 1][j], costes[i - 1][j - cuerdas[i].longitud] + cuerdas[i].coste);
		}
	}

	return costes[n][L];
}
long long int formas(vector<tCuerda> const cuerdas, int L) {

	size_t n = cuerdas.size() - 1;
	Matriz<long long int> formas(n + 1, L + 1, 0);

	// Rellenar la matriz
	formas[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		formas[i][0] = 1;
		for (int j = 1; j <= L; ++j) {
			if (cuerdas[i].longitud > j)
				formas[i][j] = formas[i - 1][j];
			else
				formas[i][j] = formas[i - 1][j] + formas[i - 1][j - cuerdas[i].longitud];
		}
	}

	return formas[n][L];
}
long long int numMin(vector<tCuerda> const cuerdas, int L) {

	size_t n = cuerdas.size() - 1;
	Matriz<long long int> minFormas(n + 1, L + 1, INF);

	// Rellenar la matriz
	minFormas[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		minFormas[i][0] = 0;
		for (int j = 1; j <= L; ++j) {
			if (cuerdas[i].longitud > j)
				minFormas[i][j] = minFormas[i - 1][j];
			else
				minFormas[i][j] = min(minFormas[i - 1][j], minFormas[i - 1][j - cuerdas[i].longitud] + 1);
		}
	}

	return minFormas[n][L];
}

// COSTE:
bool resuelveCaso() {

	int N, L;
	cin >> N >> L;
	if (!cin) return false;

	// Leemos los datos
	vector<tCuerda> cuerdas(N + 1);
	for (int i = 1; i <= N; i++) {
		tCuerda cuerda;  
		cin >> cuerda.longitud >> cuerda.coste;
		cuerdas[i] = cuerda;
	}

	long long int costeMinimo, numFormas, numMinimo;
	bool esPosible;
	
	esPosible = posible(cuerdas, L);
	costeMinimo = costeMin(cuerdas, L);
	numFormas = formas(cuerdas, L);
	numMinimo = numMin(cuerdas, L);

	if (!esPosible) cout << "NO" << endl;
	else cout << "SI " << numFormas << " " << numMinimo << " " << costeMinimo << endl;

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