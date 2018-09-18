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

using namespace std;


/*
	CASO RECURSIVO:

		
*/

void tesoro( ) {


}//recoger tesoro

bool resuelveCaso() {
	
	int puntos, sectores;
	cin >> puntos >> sectores;

	if (!cin)
		return false;

	//aumentamos en uno para que no nos cuente la pos 0
	vector<int> tiradas(sectores + 1);

	for (size_t i = 1; i <= sectores; i++){
		cin >> tiradas[i];
	}

	/*
		menor numero de dardos necesarios para conseguir la cantidad, separadopor dos puntos  
		puntuaciones que permiten conseguir ese valor, ordenadas de mayor a menor 

		Si hay varias soluciones:
			se escribira aquella cuya mayor puntuacion sea la mas alta

		Si es imposible conseguir el objetivo con las puntuaciones asignadas a los sectores de la diana, se
		escribira Imposible.
	*/


	cout << endl;

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