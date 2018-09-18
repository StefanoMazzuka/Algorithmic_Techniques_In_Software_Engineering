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
#include<string>

using namespace std;

typedef struct 
{
	int inicio;
	int fin;
}tPelicula;

bool operador(tPelicula &peliUno, tPelicula &peliDos) {
	return peliUno.fin < peliDos.fin;
}

// COSTE: O(N + n*logn) Siendo N el num de peliculas
void resuelveCaso(int N) {
	
	vector<tPelicula> peliculas(N);
	int hora, min, duracion, descanso = 10;
	char dosPuntos;
	
	for (int i = 0; i < N; i++) {
		cin >> hora >> dosPuntos >> min >> duracion;
		peliculas[i].inicio = (hora * 60) + min;
		peliculas[i].fin = peliculas[i].inicio + duracion;
	}

	sort(peliculas.begin(), peliculas.end(), operador);

	int numPelisAVer = 1;
	int ini = 0;

	for (int i = 1; i < N; i++) {
		if (peliculas[ini].fin + descanso <= peliculas[i].inicio) {
			numPelisAVer++;
			ini = i;
		}
	}

	cout << numPelisAVer << endl;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_24.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int N;
	cin >> N;
	while (N != 0) {
		resuelveCaso(N);
		cin >> N;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}