//
//  Matriz.h
//
//  Implementación de matrices (arrays bidimensionales)
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef MATRIZ_H
#define MATRIZ_H

#include <cstddef>  // size_t
#include <vector>

template <typename Object>
class Matriz {
public:
	// crea una matriz con fils filas y cols columnas,
	// con todas sus celdas inicializadas al valor e
	Matriz(size_t fils, size_t cols, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}

	// operadores para poder utilizar notación M[i][j]
	std::vector<Object> const& operator[](size_t f) const {
		return datos[f];
	}
	std::vector<Object> & operator[](size_t f) {
		return datos[f];
	}

	// métodos que lanzan una excepción si la posición no existe
	Object const& at(size_t f, size_t c) const {
		return datos.at(f).at(c);
	}
	Object & at(size_t f, size_t c) { // este método da problemas cuando Object == bool
		return datos.at(f).at(c);
	}

	size_t numfils() const { return datos.size(); }
	size_t numcols() const { return numfils() > 0 ? datos[0].size() : 0; }

	bool posCorrecta(int f, int c) const {
		return 0 <= f && f < numfils() && 0 <= c && c < numcols();
	}

private:
	std::vector<std::vector<Object>> datos;
};

#endif