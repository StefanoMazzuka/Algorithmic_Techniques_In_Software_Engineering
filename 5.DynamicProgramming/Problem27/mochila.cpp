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

// P = vector de pesos
// V = vector de valores
// M = peso máximo de la mochila
// valor = valor final de la mochila llena
// cuales = vector de objetos seleccionados

void mochila_pd(vector<int> const& P, vector<int> const& V, int M, int & valor, vector<bool> & cuales) {
	
	size_t n = P.size() - 1;
	
	Matriz<int> mochila(n + 1, M + 1, 0); // n = número de objetos, M = peso máximo de la mochila.
	
	// Rellenar la matriz
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= M; ++j) {

			if (P[i] > j) {				
				cout << P[i] << endl; // Yo
				mochila[i][j] = mochila[i - 1][j];
			}

			else mochila[i][j] = max(mochila[i - 1][j], mochila[i - 1][j - P[i]] + V[i]);
		}
	}

	valor = mochila[n][M];	// Cálculo de los objetos
	int resto = M;
	for (size_t i = n; i >= 1; --i) {
		if (mochila[i][resto] == mochila[i - 1][resto]) {
			// No cogemos objeto i
			cuales[i] = false;
		}
		else { // Sí cogemos objeto i
			cuales[i] = true;
			resto = resto - P[i];
		}
	}
}int main() {		vector<int> P = {0, 2, 3, 4, 5}; // El vector va de la posición 1 a la 4, la 0 no la tenemos en cuenta	vector<int> V = {0, 5, 4, 2, 1}; // El vector va de la posición 1 a la 4, la 0 no la tenemos en cuenta	vector<bool> cuales;	int valor, M = 10;	mochila_pd(P, V, M, valor, cuales);	system("pause");	return 0;}