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

// COSTE: O(N) Siendo N el num de libros.
bool resuelveCaso() {

	int numLibros;

	cin >> numLibros;

	if (!cin) return false;

	vector<int> libros(numLibros, 0);
	int precio;

	for (int i = 0; i < numLibros; i++) {
		cin >> precio;
		libros[i] = precio;
	}

	if (numLibros < 3) {
		cout << 0 << endl;
		return true;
	}

	sort(libros.begin(), libros.end(), greater<int>());

	int descuento = 0;

	for (int i = 2; i < numLibros; i += 3) {
		descuento += libros[i];
	}

	cout << descuento << endl;

	return true;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_19.txt");
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