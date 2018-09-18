#ifndef ARBORESCENCIA_H_
#define ARBORESCENCIA_H_

#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include "GrafoDirigido.h"

class Arborescencia{

	using Adys = std::vector<size_t>;  // lista de adyacentes a un vértice
	using Path = std::deque<size_t>;   // para representar caminos

public:

	GrafoDirigido grafo;
	size_t _V;   // número de vértices
	size_t _E;   // número de aristas
	std::vector<Adys> _adj;   // vector de listas de adyacentes
	std::vector<bool> marcado;
	std::vector<bool> marcaCiclo;

	int raiz,vertices;
	bool arborescencia = true;
	bool tieneCiclo = false;
	Path caminoCiclo;//no se desmarca al hacer recursiva
	Path camino;//se descarmca cuando hacemos recursiva

	//constructora
	Arborescencia(GrafoDirigido const& g, size_t v) : grafo(g), _V(v){

		marcado.resize(g.V(), false);
		marcaCiclo.resize(g.V(), false);

		//si es ciclico no seguimos
		DirectedCycle ciclo(g);
		tieneCiclo = ciclo.hasCycle();
		vertices = grafo.V();

		if (!tieneCiclo)
			recorridoGrafo();
		else
			arborescencia = false;
	}

	//nos dice si es o no arborescencia
	bool esArborescencia(){
		return arborescencia;
	}//arbo

	//nos dice la raiz de un grafo arborescencia
	int raizArborescencia(){
		return raiz;
	}//raiz

private:

	void recorridoGrafo(){
		
		int caminosEncontrados = 0;	
		
		for (size_t i = 0; i < vertices && esArborescencia(); i++){

			//añadimos a la cola los vertices origen
			caminoCiclo.push_front(i); 
			camino.push_front(i);

			pathTo(grafo, marcado, i, camino, caminoCiclo);

			/*
				guardaremos solo la raiz del primero que encuentre un camino que recorra todos los vertices
				por lo que los cmainosEncontrados = 0
				los caminos marcados y sin marcadar de ben de er iguales ==> no hay dos caminos a un mismo vertice
				y que recorra todos los caminos
				*/
			if (caminosEncontrados == 0 && camino.size() == caminoCiclo.size() && camino.size() == vertices){
				raiz = i;
				caminosEncontrados++;
			}
			else{
				//habria encontrado otro camino y yo no es arborescencia
				if (camino.size() == caminoCiclo.size() && camino.size() == vertices)
					arborescencia = false;
			}
			//desmarcamos el vertice origen
			marcado[i] = false;

			//limpiamos
			camino.clear();
			caminoCiclo.clear();

			//limpiamos
			marcaCiclo.clear();
			marcaCiclo.resize(vertices, false);

		}//for
		
		if (caminosEncontrados == 0)
			arborescencia = false;

	}//recorrido
	

	// Devuelve un camino desde el origen a v (vacío si no están conectados)
	void pathTo(GrafoDirigido const& g, std::vector<bool>& marcado, int v, Path& camino, Path& caminoCiclo){
				
		marcado[v] = true;
		marcaCiclo[v] = true;
	
		if (esArborescencia()){//se hace mientras tenga posibiliades de que sea arborencencia

			for (auto vs : g.adj(v)){//recorremso los vertices adyacentes del origen

				caminoCiclo.push_front(vs);//lo guardamos en la cola que comprueba si hay dos caminos

				if (!marcado[vs] && !marcaCiclo[vs]){ //lo guarda si no se han visitado los vertices todavia
					camino.push_front(vs);
					pathTo(g, marcado, vs, camino, caminoCiclo);
					marcado[vs] = false; //desmarcamos 
				}
				else{
					if (!marcado[vs] && marcaCiclo[vs])//en el caso de que encontremos dos caminos a un mismo vertice
						arborescencia = false;
				}				
			}//for

		}//if

	}//pathTo

};

#endif /* ARBORESCENCIA_H_ */