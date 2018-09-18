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

/*
Caso recursivo:
La recurrencia solo tiene sentido cuando i <= j. El caso recursivo, i < j, se
define de la siguiente manera:

Caso base:
matrices(i, i) = 0 si i = j

matrices(i, j) = míni <= k <= j − 1 { matrices(i, k) + matrices(k + 1, j) + di − 1 * dk * dj} si i < j
*/

int multiplica_matrices(vector<int> cortes, int N) {

	Matriz<int> costes(N + 1, N + 1, 0);

	// Recorrido por diagonales
	for (size_t d = 2; d <= N; d++) { // Recorre diagonales
		for (size_t i = 1; i <= N - d; i++) { // Recorre elementos de diagonal
			size_t j = i + d;
			// Calcular mínimo
			costes[i][j] = INF;
			for (size_t k = i + 1; k < j; k++) {
				int temp, coste;
				coste = 2 * (cortes[j] - cortes[i]);
				temp = costes[i][k] + costes[k][j] + coste;
				if (temp < costes[i][j]) costes[i][j] = temp; // Es mejor pasar por k		
			}
		}
	}

	return costes[1][N];
}

// Coste: O(n^3) en tiempo, O(n^2) en espacio.
void resuelveCaso(int L, int N) {

	N += 1;
	vector<int> cortes(N + 1, 0);
	cortes[N] = L;

	int corte;
	for (int i = 1; i < N; i++) {
		cin >> corte;
		cortes[i] = corte;
	}

	cout << multiplica_matrices(cortes, N) << endl;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_33.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int L, N;
	cin >> L >> N;
	while (L != 0 && N != 0) {
		resuelveCaso(L, N);
		cin >> L >> N;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}