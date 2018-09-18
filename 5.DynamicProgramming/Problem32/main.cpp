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

const int INF = 1000000000;

/*
	CASO RECURSIVO:

		i = perosona1
		j = persona2

	Matriz de adyacencia:
		redesConectadas(i, j) = 0,   si i = j (una relacion a si mismo no tiene coste)
		redesConectadas(i, j) = 1,   si hay conexion entre i, j
		redesConectadas(i, j) = Infinito,   si no hay conexion entre i, j

	Definicion de la funcion:
	C^k(i, j) = coste mínimo para ir de i a j pudiendo utilizar vértices intermedios entre 1 y k.

	Caso recursivo:
	C^k(i, j) = min(C^k-1(i, j), C^k-1(i, k) + C^k-1(k, j))

	Caso base (cuando k = 0):
	C^0(i, j) = G(i, j),   si i != j
	C^0(i, j) = 0,   si i = j


	COSTE del algoritmo de Floid es O(n^3)
*/


void resuelve(Matriz<int> const& grafo, Matriz<int> & C, Matriz<size_t> & camino){

	size_t n = grafo.numfils() - 1;
	C = grafo;
	camino = Matriz<size_t>(n + 1, n + 1, 0);

	// actualizaciones de la matriz
	for (size_t k = 1; k <= n; ++k){
		for (size_t i = 1; i <= n; ++i){
			for (size_t j = 1; j <= n; ++j) {

				int temp = C[i][k] + C[k][j];

				if (temp < C[i][j]) { // es mejor pasar por k
					C[i][j] = temp;
					camino[i][j] = k;
				}
			}//j
		}//i
	}//k

	int sol = 0;
	for (int i = 1; i <= n; i++){
		for (int j = i + 1; j <= n; j++){

			if (C[i][j] > sol)
				sol = C[i][j];
		}
	}//i

	if (sol == INF)
		cout << "DESCONECTADA" << "\n";
	else
		cout << sol << "\n";
}

int asignarNumPersonas(string p, vector<string>& per, vector<int>& nodos){

	bool encontrada = false;
	int i = 1;

	while (!encontrada){

		//si la persona ya existe (se encuentra en el vector de los nombre)
		if (per[i] == p)
			encontrada = true;

		//si en la posicion de vector de nodos esa persona no existe
		//por loq ue tiene asignado un -1 ==> añadimos persona
		if (nodos[i] == -1){
			encontrada = true;
			per[i] = p;
			nodos[i] = i;
		}

		i++;
	}

	//-1 porque los nodos empiezan desde 0 no 1
	return i - 1;
}

//
bool resuelveCaso() {

	int personas, relaciones;
	cin >> personas >> relaciones;

	if (!cin)
		return false;

	//creamos matriz adyacencia y lo inicializamos a INF
	Matriz<int> grafo(personas + 1, personas + 1, INF);

	// Ponemos a 0 el coste de cada vertice consigo mismo
	for (size_t i = 0; i <= personas; i++){
		grafo[i][i] = 0;
	}

	/*
	creamos dos vectores:
	1. para guardar los nombres de las personas
	2. para asignarles un numero (numero del nodo en el que esta la persona)
	*/

	vector<string> nomPersonas(personas + 1);
	vector<int> nodos(personas + 1, -1);
	string p1, p2;


	/*
	leemos las personas y relleanmos sus costes (1)
	entre las dos personas x<--->y
	*/
	for (size_t i = 0; i < relaciones; i++){
		cin >> p1 >> p2;

		/*
		comrpobamos si las personas que leemos ya estan en el vector
		y optenemos el nodo en el que se encuetra o
		o se encontraba (si ya estaba)s
		*/

		int nodoP1 = asignarNumPersonas(p1, nomPersonas, nodos);
		int nodoP2 = asignarNumPersonas(p2, nomPersonas, nodos);

		//asignamos los costes
		grafo[nodoP1][nodoP2] = 1;
		grafo[nodoP2][nodoP1] = 1;
	}


	Matriz<int> C(0, 0);
	Matriz<size_t> camino(0, 0);
	resuelve(grafo, C, camino);
	

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