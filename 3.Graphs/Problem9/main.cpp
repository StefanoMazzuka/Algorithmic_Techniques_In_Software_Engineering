/*
GRUPO:
TAIS26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"

// recorrido en profundidad desde v
//seguimos el camino a traves de las aritas de cada vertice adyacente del que partidos
//asi recorremos todos los amigos de uno y se suma tambien a que son amigos
//del vertice orginal
void dfs(Grafo const& grafo, int v, int &verticesVisitados, std::vector<bool> &marcado) {

	verticesVisitados++;
	marcado[v] = true; //marcamos el vertice del que recorremos sus adyacentes 

	for (auto w : grafo.adj(v)) { //recorremos sus adyacentes

		if (!marcado[w]) {//si el vertice adyacente no esta marcado nos recorremos sus adyacentes 
			dfs(grafo, w, verticesVisitados, marcado);
		}
	}//for
}

// resolvemos cada caso de prueba
/*
	COSTE: O(n) siendo n el numero de amigos mas paresAmigos
	porque cada amigo puede tener mas de un amigo
*/
void resuelveCaso(int personasCiudad, int paresAmigos) {

	/*
		creamos un grafo con vertices el nuemro de personas de la ciudad
		y aristas las parejas que hay
	*/
	Grafo grafo = Grafo(personasCiudad);

	//creamos el grafo añadiendo las parejas
	while (paresAmigos != 0){

		int v1, v2;
		std::cin >> v1;
		std::cin >> v2;

		grafo.ponArista(v1 - 1, v2 - 1); //añadimos dos vertices al grafo con una arista restamos para que empiece en 0

		paresAmigos--;
	}
	
	int maxGrupoAmigos = 0;
	std::vector<bool> marcado(personasCiudad, false); //creamos un vector para marcarlos tamaño nuemro personasCiudad inicializado a false

	for (int i = 0; i < personasCiudad; i++) {

		int verticesVisitados= 0;

		dfs(grafo, i, verticesVisitados, marcado); //recorremos cada vertice en profundidad

		if (verticesVisitados > maxGrupoAmigos) { //si el valor apartir del vertice recorrido es mayor pasa a ser el maxGrupoAmigos
			maxGrupoAmigos = verticesVisitados;
		}
	}

	std::cout << maxGrupoAmigos << "\n";

}//metodo


int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	int casos;
	std::cin >> casos;

	while (casos != 0){

		int personasCiudad, paresAmigos;
		std::cin >> personasCiudad;
		std::cin >> paresAmigos;

		if (paresAmigos != 0)
			resuelveCaso(personasCiudad, paresAmigos);
		else
			std::cout << "1 \n"; //si solo hay una persona

		casos--;
	}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}