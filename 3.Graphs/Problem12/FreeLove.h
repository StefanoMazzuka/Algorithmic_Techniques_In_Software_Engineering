#ifndef FREELOVE_H_
#define FREELOVE_H_

#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

/*
estructura nodo que guarda la posicion en la matriz
y el nodoque ocupa
*/
struct infoNodo{
	size_t i;
	size_t j;
	size_t nodo;
};

class FreeLove{

	//mapas 
	using Mapa = std::vector<std::string>;
	using MapaNodos = std::vector<std::vector<size_t>>;

public:

	size_t caminoMinimo, F, C, nodo;
	size_t filaE, columnaE, filaP, columnaP;
	infoNodo nodoP;
	bool finColocaMuro = false;
	Mapa mapa;
	MapaNodos mapaNodos;

	//vectores bidimensionales de marcado
	std::vector<std::vector<bool>> marcadoSensor;
	std::vector<std::vector<bool>> marcado;
	std::vector<std::vector<bool>> marcadoMuro;

	//vectores para el recorrido en anchura
	std::vector<std::vector<size_t>> distTo;   // distTo[v] = número de aristas en el camino s-v más corto
	std::queue<infoNodo> colaNodos;

	FreeLove(Mapa const& g) : mapa(g), F(g.size()), C(g[0].size()),
		nodo(0), caminoMinimo(0){

		//inicializacion de todos los vectores
		marcadoSensor.assign(F, std::vector<bool>(C, false));
		marcado.assign(F, std::vector<bool>(C, false));
		marcadoMuro.assign(F, std::vector<bool>(C, false));
		mapaNodos.assign(F, std::vector<size_t>(C, 0));
		distTo.assign(F, std::vector<size_t>(C, 0));

		filaE = -1; columnaE = -1; //posicion E
		filaP = -1;	columnaP = -1; //posicion P

		crearMapa(mapa);
		buscaCamino();
	}
	
	//en el caso de encontrarse camino la distancia minima
	int minimo(){
		return caminoMinimo;
	}

private:

	void recorridoEnAnchura(int i, int j){

		distTo[i][j] = 0;
		marcado[i][j] = true;

		infoNodo n;
		n.i = i;
		n.j = j;
		n.nodo = mapaNodos[i][j];

		colaNodos.push(n);

		int ni, nj;

		std::pair <int, int> dirCamino[4] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

		while (!colaNodos.empty()) {

			infoNodo v = colaNodos.front();
			i = v.i;
			j = v.j;
			colaNodos.pop();

			for (auto d : dirCamino){

				ni = i + d.first;
				nj = j + d.second;

				if ((0 <= ni) && (ni < F) && (0 <= nj) && (nj < C) && (ni != i || nj != j) && mapa[ni][nj] != '#'){

					if (!marcadoSensor[ni][nj] && !marcado[ni][nj]){

						distTo[ni][nj] = distTo[i][j] + 1;
						marcado[ni][nj] = true;

						infoNodo n;
						n.i = ni;
						n.j = nj;
						n.nodo = mapaNodos[ni][nj];
						colaNodos.push(n);

					}
				}//dentro de matriz				
			}//for
		}

	}//recorrido en anchura

	void buscaCamino(){

		if (!marcadoSensor[filaE][columnaE]  &&  !marcadoSensor[filaP][columnaP] ){
			recorridoEnAnchura(filaE, columnaE);
			caminoMinimo = distance(filaP, columnaP);
		}

	}//buscaCamino

	void bloqueosMuros(int fk, int ck, int& fm, int& cm, int& k, bool bloqueo){

		while (k >= 0 && !finColocaMuro){

			if ((0 <= fm) && (fm < F) && (0 <= cm) && (cm < C)){
				k--;

				if (mapa[fm][cm] == 'E'){
					filaE = fm;
					columnaE = cm;
				}
				else{
					if (mapa[fm][cm] == 'P'){
						filaP = fm;
						columnaP = cm;
					}
				}//e

				if (bloqueo)
					marcadoMuro[fm][cm] = true;
				else
					marcadoMuro[fm][cm] = false;

				if (fm < fk){//norte
					fm = fm - 1;
					bloqueosMuros(fk, ck, fm, cm, k, bloqueo);
				}
				else{

					if (fm > fk){//sur
						fm = fm + 1;
						bloqueosMuros(fk, ck, fm, cm, k, bloqueo);
					}
					else{
						if (cm > ck){//este
							cm = cm + 1;
							bloqueosMuros(fk, ck, fm, cm, k, bloqueo);
						}
						else{
							if (cm < ck){
								cm = cm - 1;
								bloqueosMuros(fk, ck, fm, cm, k, bloqueo);
							}
						}//else3
					}//else2
				}//else1
			}
			else
				finColocaMuro = true;

		}//while

	}

	void quitarBloqueoMuros(int i, int j){

		int k = int(mapa[i][j] - 48); //calculamos el valor de K, restamos 48 valor de 0 en ASCII
		int ni, nj, aux = 1;
		int x, nni, nnj;

		std::pair <int, int> dir[4] = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };

		ni = i, nj = j;
		while (aux < (k + 1)){
												//fila		//fila		//columa	//columna
			std::pair <int, int> dir[4] = { { -aux, 0 }, { aux, 0 }, { 0, aux }, { 0, -aux } };

			for (auto d : dir){

				ni = i + d.first;
				nj = j + d.second;

				if ((0 <= ni) && (ni < F) && (0 <= nj) && (nj < C)){ //si no se sale de la matriz

					if (mapa[ni][nj] == '#'){ //bloqueamos en el caso de que sea # y k > 1
						x = (k - aux), nni = ni, nnj = nj;
						finColocaMuro = false;
						bloqueosMuros(i, j, nni, nnj, x, false);
					}
				}//si esta dentro

			}//dir

			aux++;

		}//while

	}//ponerSensor

	void ponerSensor(int i, int j){

		int k = int(mapa[i][j] - 48); //calculamos el valor de K, restamos 48 valor de 0 en ASCII
		int ni, nj, aux = 1;
		int x, nni, nnj;

		marcadoSensor[i][j] = true;

		std::pair <int, int> dir[4] = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };

		ni = i, nj = j;
		while (aux < (k + 1)){
												//fila		//fila		//columa	//columna
			std::pair <int, int> dir[4] = { { -aux, 0 }, { aux, 0 }, { 0, aux }, { 0, -aux } };

			for (auto d : dir){

				ni = i + d.first;
				nj = j + d.second;

				if ((0 <= ni) && (ni < F) && (0 <= nj) && (nj < C)){ //si no se sale de la matriz

					if (mapa[ni][nj] == '#'){ //bloqueamos en el caso de que sea # y k > 1
						x = (k - aux), nni = ni, nnj = nj;
						finColocaMuro = false;
						bloqueosMuros(i, j, nni, nnj, x, true);
					}

					if (!marcadoMuro[ni][nj])//si no esta marcado por muro colocamos sensor
						marcadoSensor[ni][nj] = true;

				}//si esta dentro
			}//dir

			aux++;

		}//while

	}//ponerSensor

	//leemos el mapa colocando los sensores
	void crearMapa(Mapa const& mapa){

		for (size_t i = 0; i < F; i++){
			for (size_t j = 0; j < C; j++){

				/*
				creamos los nodos en una nueva matriz
				guardando su posicion y el nodo
				*/
				infoNodo in;
				in.i = i;
				in.j = j;
				in.nodo = nodo;
				mapaNodos[i][j] = nodo;

				nodo++;

				//si no es un cat-K no se hace nada
				if (mapa[i][j] != '.' && mapa[i][j] != 'E' && mapa[i][j] != 'P' && mapa[i][j] != '#'){
					ponerSensor(i, j);
					quitarBloqueoMuros(i, j);
				}

				if (mapa[i][j] == 'E'){
					filaE = i;
					columnaE = j;
				}
				else{
					if (mapa[i][j] == 'P'){
						filaP = i;
						columnaP = j;
					}
				}//e


			}//forj
		}//fori

	}//crearMapa

	//nos devulve el menor camino hasta la posicion que le pasamos
	size_t distance(size_t i, size_t j) const {
		return distTo[i][j];
	}
};

#endif /* FREELOVE_H_ */