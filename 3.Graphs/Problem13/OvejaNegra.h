#ifndef FREELOVE_H_
#define FREELOVE_H_

#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>

class OvejaNegra {
	
	using Mapa = std::vector<std::string>;
	

public:

	int oBlancas, F, C;
	Mapa mapa;
	std::vector<std::vector<bool>> marcado;

	OvejaNegra(Mapa const& g) : mapa(g), F(g.size()), C(g[0].size()), oBlancas(0){
		
		oBlancas = 0;
		marcado.assign(F,std::vector<bool>(C,false));

		crearMapa(mapa);	
	}

	/*
		restamos 1 al numero total de puntos encontrados, porque desde un punto llegamso a todos los que estes accesibles
		por lo que llegaria a todos los del fondo y si encuentra otro ya seria dentro de una oveja
		por eso retamos porque si es 1 no vale como oveja
	*/
	int ovejasBlancas(){
		return oBlancas-1;
	}

private:
	
	void recorremosMapa(int i, int j){

		marcado[i][j] = true;

		std::pair<int, int> dirs[4] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

		for (auto d : dirs){

			int ni = i + d.first;
			int nj = j + d.second;

			if ((0 <= ni) && (ni < F) && (0 <= nj) && (nj < C) && (ni != i || nj != j)){

				if (mapa[i][j] == '.' && !marcado[ni][nj])
					recorremosMapa(ni, nj);

			}
		}//for dir
	}

	void crearMapa(Mapa const& mapa){

		for (size_t i = 0; i < F; i++){
			for (size_t j = 0; j < C; j++){

				if (mapa[i][j] == '.' && !marcado[i][j]){
					oBlancas++;
					recorremosMapa(i, j);
				}
								
			}//forj
		}//fori

	}//crearMapa

};

#endif /* FREELOVE_H_ */