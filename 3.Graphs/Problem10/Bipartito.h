
/*
	clase Bipartito que extiende de la clase de grafo
	y nso dirá si un grafo es biparito o no
*/

#ifndef BIPARTITO_H_
#define BIPARTITO_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include "Grafo.h"

using Adys = std::vector<size_t>;  // lista de adyacentes a un vértice

class Bipartito{

	Grafo _G;   // grafo que recibimos
	size_t _V;   // número de vértices
	size_t _E;   // número de aristas	
	std::vector<Adys> _adj;   // vector de listas de adyacentes de lo vertices

	bool bipartito = true; //atributo general que lo modificamos esBipartito 
	int color = 1;		   // color con el que pintamos, empezamos por 1
	std::vector<bool>marcado; //vector para marcar los vertices visitados
	std::vector<int>colores;	//vector para indicar de que color esta el vertice

	public:

	//constructor
	Bipartito(Grafo const& g, size_t vertice) : _G(g), _V(vertice){

		//inicializamos vectores  el bool a false el int a 0
		marcado.resize(g.V(), false);
		colores.resize(g.V(), 0);

		//llamaos al dfs para recorrido en profundidad por vertices
		dfs(g,vertice);

	}//bipartito

	/* 
		COSTE: O(n) sinedo n el numero  de vertices
		recorrido en profundidad por vertices
	*/
	void dfs(Grafo g, int v){

		for (int i = 0; i < g.V(); i++){
			if (!marcado[i])
				esBipartito(g, colores, i, color);
		}
	}//dfs

	//nos dice si es bipartito o no
	bool GrafoBipartito(){
		return bipartito;
	}//GrafoBipartito



	private:
	
	/*
		COSTE:O(n) siendo n el numero de aristas que se recorrera en cada vertice

		metodo que recorre los vertices adyacentes a partir de uno
		va  cambiando de color cuando cambia de vertice
		si el color es igual en vertice origen y destino ya no es bitartito
	*/
	void esBipartito(Grafo g, std::vector<int>& colores, int v, int& colorMarcar){

		marcado[v] = true;
		colores[v] = colorMarcar;
		cambioColor(colorMarcar);

		if (bipartito){

			for (auto vs : g.adj(v)){

				if (!marcado[vs]){
					esBipartito(g, colores, vs, colorMarcar);
					cambioColor(colorMarcar); //comentario al final								
				}
				else
					if (colores[v] == colores[vs])//coincide el color en dos vertices que tienen arista ==> false
						bipartito = false;
			}//for
		}//if

	}//esBipartito
	

	/*
		ponemos color opuesto del vertice de origen
	*/
	void cambioColor(int& colorMarcar){

		if (colorMarcar == 1)
			colorMarcar = 2;
		else
			colorMarcar = 1;

	}//cambioColor

};

#endif /* BIPARTITO_H_ */


/*
EJ: 0___1
\
2

¿Por qué se cambia el color después de la llamada recursiva?

empezamos en = lo marcamso con color 1
pasa a seguir con su adyacente 1 (recursivo) y es marcado con el color 2
su adyacente solo es 0 y sale que != color
termina la rescursividad

_Si no cambiamos de color despues de la recursividad
vuelve al 0 y se va a su otro adyacente el 2
cambia de color a 1
y comprueba con su adyacente solo 0 y sale mismo colo
==> no es bipartito FALSO

_cambiamos en color despues de la recursividad
cambia el color a 1, que es el color del vertice de origen el 0
porque volveremos a partir de el para ver mas adyacentes
su adyacente es 2 lo marca con color 2
recursiva comprueba adyacentes de 2 y es solo el 0
color != termian recursividad
==> si es bipartito VERDADERO
*/