#ifndef  BARROCITY_H_
#define BARROCITY_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <climits>
#include "GrafoValorado.h"
#include "IndexPQ.h"

class CaminoCole{
	
public:

	GrafoValorado<int> grafo;	//creamos un grafoValorado
	std::vector<int> distTo;
	std::vector<int> edgeTo;
	IndexPQ<int> pq;
	int vertices;

	CaminoCole(GrafoValorado<int> const& gv, int aristas) : grafo(gv), vertices(gv.V()), pq(gv.V()){

		//inicializamos los vectores
		distTo.resize(vertices, INT_MAX); //10^9 lo usariamos si fuese para sumar
		edgeTo.resize(vertices, 0);
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
		si lo cumple recorremos todos los vertices marcados y sumamos su distancia
		que será la menor en el recorrido
	*/
	int caminoMinimo(){
		return edgeTo[vertices-1];
	}//camino

	void recorrerGrafo(int& v){

		distTo[v] = 0;
		edgeTo[0] = 1;
		pq.push(0, 0);

		while (!pq.empty()) {

			int v = pq.top().elem;
			pq.pop();
			
			for (Arista<int> a : grafo.adj(v))
				relax(a, v);

		}//while
	}//recorrer

private:
	
	void relax(Arista<int> a, int v){
				
		int w = a.otro(v);

		if (distTo[v] + a.valor() <= distTo[w]){

			if (distTo[v] + a.valor() < distTo[w])
				edgeTo[w] = edgeTo[v];
			else
				edgeTo[w] += edgeTo[v];
			
			//actualizamos destino
			distTo[w] = distTo[v] + a.valor();

			pq.update(w, distTo[w]);
		}
	}

};

#endif /* BARROCITY_H_ */