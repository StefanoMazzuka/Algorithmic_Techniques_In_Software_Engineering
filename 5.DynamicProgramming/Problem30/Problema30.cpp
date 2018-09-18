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

/*
Caso recursivo:

Caso base:
palabra de longitud 0

letras[pos][i] = letras[pos + 1][i - 1]                           si palabra[pos] == palabra[i]
letras[pos][i] = min(letras[pos + 1][i], letras[pos][i - 1]) + 1  si palabra[pos] != palabra[i]
*/

int numLetrasParaSerPalindromo(string palabra) {

	size_t n = palabra.size();
	Matriz<int> letras(n, n, 0);

	for (int j = 1; j < n; j++) {
		int pos = 0;
		for (int i = j; i < n; i++) {
			if (palabra[pos] == palabra[i]) letras[pos][i] = letras[pos + 1][i - 1];
			else letras[pos][i] = min(letras[pos + 1][i], letras[pos][i - 1]) + 1;
			pos++;
		}
	}

	return letras[0][n - 1];
}

// COSTE: O([n^2 - n] / 2)

//          2
//        _n__-__n__
//            2
bool resuelveCaso() {

	string palabra;
	cin >> palabra;
	if (!cin) return false;

	int numLetras = numLetrasParaSerPalindromo(palabra);

	cout << numLetras << endl;

	return true;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_30.txt");
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