//
//  ConjuntosDisjuntos.h
//
//  Implementación de estructuras de partición o conjuntos disjuntos
//  con unión por tamaño y compresión de caminos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/9/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef CONJUNTOSDISJUNTOS_H_
#define CONJUNTOSDISJUNTOS_H_

#include <vector>
#include <iostream>

class ConjuntosDisjuntos {
public:
    
    // crea una estructura de partición con los elementos 0..N-1, cada uno en un conjunto
    ConjuntosDisjuntos(size_t N) : _size(N), _count(_size), id(_size, -1) {}
    
    // devuelve el número de conjuntos disjuntos
    size_t count() const { return _count; }
    
    //  devuelve el identificador del conjunto que contiene a p
    size_t buscar(size_t p) const {
        if (id.at(p) < 0) // es una raíz
            return p;
        else
            return id[p] = int(buscar(id[p]));
    }

    // unir los conjuntos que contengan a p y q
    void unir(size_t p, size_t q) {
        auto i = buscar(p);
        auto j = buscar(q);
        if (i == j) return;
        if (id[i] < id[j]) { // i es la raíz del mayor árbol
            id[i] += id[j]; id[j] = int(i);
        } else {
            id[j] += id[i]; id[i] = int(j);
        }
        _count--;
    }

    size_t size(size_t p) const {
        return -id[buscar(p)];
    }
    
    bool unidos(size_t p, size_t q) const {
        return buscar(p) == buscar(q);
    }

protected:
    size_t _size;            // los elementos son 0 .. _size-1
    size_t _count;           // número de conjuntos disjuntos
    mutable std::vector<int> id;  // si id[i]>=0 es el padre de i, si no es el tamaño del conjunto de i
    
};


#endif
