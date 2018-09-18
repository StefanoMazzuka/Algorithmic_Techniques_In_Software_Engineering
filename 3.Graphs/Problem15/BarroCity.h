#ifndef  BARROCITY_H_
#define BARROCITY_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include "GrafoValorado.h"
#include "PriorityQueue.h"

class BarroCity{

/*
	creamos una estructura con la informacion de las aristas para poder ordenarlas en la cola
	por su valor y poder obtener sus vertices de origen y destino
*/
struct informacionArista{
		int origen;
		int destino;
		int coste;

		//sobreescribimos el operador < ordenarlo segun el coste de la arista
		bool operator<(const informacionArista &nuevaArista) const {
			return coste < nuevaArista.coste;
		}
};

public:
		
	GrafoValorado<int> grafo;	//creamos un grafoValorado
	PriorityQueue<informacionArista> pq;	//cola de tipo informacion arista

	std::vector<bool> marcado;	//marcamos los vertices recorridos

	std::vector<int> distTo;		  //distTo[v] = número de aristas en el camino s-v más corto
	std::vector<Arista<int>> edgeTo;  //arista que llega hasta el indice

	int minimo, vertices, aristasColocadas;

	BarroCity(GrafoValorado<int> const& gv, int aristas) : grafo(gv), vertices(gv.V()),pq(gv.V()){

		minimo = 0;
		aristasColocadas = 0;

		//inicializamos los vectores
		marcado.resize(vertices, false);
		edgeTo.resize(vertices);

		//inicializamos la distancia al mayor maximo permitido para que siempre el primer coste sea menor
		distTo.resize(vertices,100001); 	

	}

	/*
		colocamos las aristas en el grafo creando cada una de ellas
		con el origen, destino y valor
	*/
	void colocarArista(int vOrigen, int vDestino, int coste){
		Arista<int> a(vOrigen, vDestino, coste);
		grafo.ponArista(a);
	}
	 
	/*
		calculamos el rcorrido con menor coste
		si las aristas que hemos colocado son menores que el numero de vertices ==> que no se ha llegado a todos los vertices
		si lo cumple recorremso todos los vertices marcados y sumamos su distancia
			que será la menor en el recorrido
	*/
	int caminoMinimo(){

		if(aristasColocadas < vertices)
			return 0;

		for (int i = 0; i < vertices; i++){

			if (marcado[i])
				minimo += distTo[i];

		}
		
		return minimo;
	}//camino

	void recorrerGrafo(){
		
		/*
			empezamos a recorrer el grafo desde el vertice 0 y la distancia hasta este vertice también será 0
			mientras tengamos vertices que recorrer en la pila seguimos recorriendo
			la pila es de tipo arista por lo que debemos sacar del elemento el vertice destino
			para la proxima llamada porque el de origen es el que recorre la arista
			preguntamos que no este marcado para que no se repitan un vertice al que le lleguen varias aristas
		*/
		recorrerGrafoAux(0);
		distTo[0] = 0;

		while (!pq.empty()) {
			informacionArista v = pq.top();
			pq.pop();
			if (!marcado[v.destino])
				recorrerGrafoAux(v.destino);
		}

	}//recorrer

private:
	
	/*
		marcamos le vertice del que vamos a recorrer sus adyacentes
		sumamos las aristas (con esto controlamos los vertices visitados)
		recorremos cada adyacente del vertice de origen:
			si el valor que tiene en su distancia es > al nuevo valor de la arista 
			actualiza el nuevo coste hasta el vertice
			actualiza la información de la arista (vertice origen, destino y coste)
			creamos el objeto informacionArista (con la informacion de la arisa actual) y lo añadimos a la cola
				la prioridad de la cola la definimos en la estructura y es segun el coste
	*/
	void recorrerGrafoAux(int v){

		marcado[v] = true;
		aristasColocadas++;

		for (Arista<int> a : grafo.adj(v)){

			size_t destino = a.otro(v);
			int valor = a.valor();
			
			if (!marcado[destino]){

				if (valor < distTo[destino]) {//si lo nuevo que llega es menor

					edgeTo[destino] = a;
					distTo[destino] = valor;

					informacionArista arista;
						arista.origen = a.uno();
						arista.destino = destino;
						arista.coste = valor;

					pq.push(arista);
				}
			}//!maracado			

		}//for

	}//recorrerAux
};

#endif /* BARROCITY_H_ */