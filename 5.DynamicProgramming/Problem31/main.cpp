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
#include <algorithm>
#include<string>
#include"Matriz.h"

using namespace std;


/*
	CASO RECURSIVO:

	i:indice cadena1
	j:indice cadena2

	Casos base:
	subCadenaMayor (0,0); = 0  si cadenas son vacias

	Caso recursivo:
	subCadenaMayor(i-1,j-1)+1;							  cadena1[i] = cadena2[j]
	max(subCadenaMayor(i-1,j), subCadenaMayor(i,j-1) );	  cadena1[i] "= cadena2[j]

	Coste: O(N*M) en recorrer la matriz donde N es la longitud de la palabra colocada en las filas y M
	la longitud de la palabra colocada en las columnas
*/

void subCadenaMayor(string cadena1, string cadena2, int& maxLong){

	int row = cadena1.size();
	int col = cadena2.size();
	Matriz<int> matrizSub(row + 1, col + 1,0);

	for (size_t i = 1; i <= row; i++){
		for (size_t j = 1; j <= col; j++){

			if (cadena1[i] == cadena2[j])
				matrizSub[i][j] = matrizSub[i-1][j-1] + 1;
			else
				matrizSub[i][j] = max(matrizSub[i-1][j], matrizSub[i][j-1]);
		}
	}//for i


	//restamos el espacio que pusimos por leer con cin
	maxLong = matrizSub[row][col]-1;
}

bool resuelveCaso() {
	
	string c1, c2, cadena1=" ", cadena2=" ";
	cin >> c1 >> c2;

	/*
		como leemos con cin los valores de las cadenas estas de la 0 hasta longitud - 1
		por eso metemos un esapcio delante para luego ir de i a longitud de la cadena
	*/
	cadena1 += c1;
	cadena2 += c2;

	if (!cin)
		return false;

	int maxLong;
	subCadenaMayor(cadena1,cadena2,maxLong);
	cout << maxLong << endl;
	
	return true;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	
	while (resuelveCaso());

	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}