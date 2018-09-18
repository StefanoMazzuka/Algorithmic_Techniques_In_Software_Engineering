#ifndef PRETOLEROS_H_
#define PRETOLEROS_H_

#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>
#include "ConjuntosDisjuntos.h"

class Petroleros {

	using Mapa = std::vector<std::string>;

public:

	int max, F, C, contaminado, nodo, x, y;
	Mapa mapa;
	ConjuntosDisjuntos cd;

	std::vector<std::vector<bool>> marcado;
	std::vector<std::vector<int>> mapaNodos;

	Petroleros(Mapa const& m, int filas, int columnas) : mapa(m), cd(filas*columnas), F(filas), C(columnas) {

		contaminado = 0;
		max = 0;
		nodo = 0;

		marcado.assign(F, std::vector<bool>(C, false));
		mapaNodos.assign(F, std::vector<int>(C, -1));

		colocarNodos();
		crearMapa(mapa);
	}
	
	/*
		añadimos la nueva mancha directamente #
		y recorremos las ocho direcciones de la mancha si hay un/ o varios conjunto al lado se une a ellos
		sino simplemente se qeuda marcado en el mapa como otro conjunto disjunto mas
	*/
	void unirMancha(int i, int j){

		mapa[i][j] = '#';

		std::pair<int, int> dirs[8] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 },
		{ -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 } };

		for (auto d : dirs){

			int ni = i + d.first;
			int nj = j + d.second;

			if ((0 <= ni) && (ni < F) && (0 <= nj) && (nj < C) && (ni != i || nj != j)){

				if (mapa[ni][nj] == '#'){

					bool unidos = cd.unidos(mapaNodos[ni][nj], mapaNodos[i][j]);

					if (!unidos)
						cd.unir(mapaNodos[ni][nj], mapaNodos[i][j]);
				}//ir #
			}
		}//for dir

		contaminado = cd.size(mapaNodos[i][j]);

		if (contaminado > max)
			max = contaminado;
	
	}

	int contaminacionMayor(){
		return max;
	}

private:
	
	void colocarNodos(){

		for (size_t i = 0; i < F; i++){
			for (size_t j = 0; j < C; j++){
				mapaNodos[i][j] = nodo;
				nodo++;
			}
		}

	}
	
	/*
		al ser el primer recorrido si es necesario recorrerse todo el mapa
		y marcar cada mancha

		contaminado = cd.size(mapaNodos[i][j]);
		con size llamando al conjuntoDisjunto nos devuevle el numero de nodos
		que tienen asociado al misma raiz del que pasamos

		 [0][1][2][3][4][5][6]
		 ---------------------
		 [0][0][2][0][2][5][0]

		 un grafo lo forman {0,1,3,6} que tiene  como padre el 0
		 size si pasamos el 6 (sin ser el el 'padre') nos daria 4
		 porque existen 4 elemtnos en el array que tienen su mismo padre

		  grafo {2,4}
		  grafo {5}
	*/
	void crearMapa(Mapa const mapa){

		for (size_t i = 0; i < F; i++){
			for (size_t j = 0; j < C; j++){

				if (mapa[i][j] == '#' && !marcado[i][j]){
					recorremosMapa(i, j);
					contaminado = cd.size(mapaNodos[i][j]);
				}

				if (contaminado > max)
					max = contaminado;

			}//forj
		}//fori

	}//crearMapa

	/*
		lo utilizamso solo en el primer recorrido donde si es necesario ir marcando
		comrpobamso que si es # si se puede unir con otro conjunto por eso 
		comprobamos aunque este marcado
	*/
	void recorremosMapa(int i, int j){
		
		marcado[i][j] = true;

		//ocho direcciones contemplamo las diagonales
		std::pair<int, int> dirs[8] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 },
										{ -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 } };

		for (auto d : dirs){

			int ni = i + d.first;
			int nj = j + d.second;

			if ((0 <= ni) && (ni < F) && (0 <= nj) && (nj < C) && (ni != i || nj != j)){

				if (mapa[ni][nj] == '#'){

					bool unidos = cd.unidos(mapaNodos[ni][nj], mapaNodos[i][j]);

					if ( (marcado[ni][nj] && !unidos) || !marcado[ni][nj] ){
						//[ni][nj] se une a [i][j]
						cd.unir(mapaNodos[ni][nj], mapaNodos[i][j]);
						recorremosMapa(ni, nj);
					}
					
				}//ir #
			}
		}//for dir
	}

};

#endif /* PRETOLEROS_H_ */