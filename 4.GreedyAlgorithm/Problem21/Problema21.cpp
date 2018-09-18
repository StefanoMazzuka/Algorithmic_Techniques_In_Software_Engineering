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

using namespace std;

// COSTE: O(N + N*logN) Siendo N el num de usuarios
bool resuelveCaso() {

	int pesoMax, numUsuarios;
	cin >> pesoMax >> numUsuarios;

	if (!cin) return false;

	vector<int> usuarios(numUsuarios);

	for (int i = 0; i < numUsuarios; i++) {
		int peso;
		cin >> peso;
		usuarios[i] = peso;
	}

	sort(usuarios.begin(), usuarios.end(), less<int>());
	int numViajes = 0, i = 0, j = numUsuarios - 1;

	while (i <= j) {
		if (usuarios[i] + usuarios[j] <= pesoMax) {
			i++;
			j--;
			numViajes++;
		}
		else {
			j--;
			numViajes++;
		}
	}

	cout << numViajes << endl;

	return true;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_21.txt");
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