/*
GRUPO:
TAIS 26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

// COSTE: O(N) Siendo N el num de pertidos.
void resuelveCaso(int numPartidos) {

	vector<int> rivales(numPartidos);
	vector<int> boston(numPartidos);
	int resultado;

	for (int i = 0; i < numPartidos; i++) {
		cin >> resultado;
		rivales[i] = resultado;
	}

	for (int i = 0; i < numPartidos; i++) {
		cin >> resultado;
		boston[i] = resultado;
	}

	sort(rivales.begin(), rivales.end(), less<int>());
	sort(boston.begin(), boston.end(), greater<int>());

	int exitoMax = 0, i = 0;

	while (boston[i] - rivales[i] > 0 && i < numPartidos) {
		exitoMax += boston[i] - rivales[i];
		i++;
	}

	cout << exitoMax << endl;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_22.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int numPartidos;
	cin >> numPartidos;
	while (numPartidos != 0) {
		resuelveCaso(numPartidos);
		cin >> numPartidos;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}