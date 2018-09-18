//
//  GrafoValorado.h
//
//  Implementación de grafos no dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFOVALORADO_H_
#define GRAFOVALORADO_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

template <typename Valor>
class Arista_impl;

template <typename Valor>
class Arista {
public:
    Arista();
    Arista(size_t v, size_t w, Valor valor);
    size_t uno() const;
    size_t otro(size_t vert) const;
    Valor valor() const;
    void print(std::ostream & o = std::cout) const;
private:
    std::shared_ptr<Arista_impl<Valor>> pimpl;
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, Arista<Valor> const& ar){
    ar.print(o);
    return o;
}

template <typename Valor>
inline bool operator<(Arista<Valor> const& a, Arista<Valor> const& b)
{
    return a.valor() < b.valor();
}

template <typename Valor>
inline bool operator>(Arista<Valor> const& a, Arista<Valor> const& b)
{
    return a.valor() > b.valor();
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:

    /**
     * Crea un grafo valorado con V vértices, sin aristas.
     */
    GrafoValorado(size_t v) : _V(v), _E(0), _adj(_V) { }
    
    /**
     * Devuelve el número de vértices del grafo.
     */
    size_t V() const { return _V; }
    
    /**
     * Devuelve el número de aristas del grafo.
     */
    size_t E() const { return _E; }
    
    /**
     * Añade la arista v-w al grafo.
     * @throws invalid_argument si algún vértice no existe
     */
    void ponArista(Arista<Valor> const& arista);
    
    /**
     * Devuelve la lista de adyacencia de v.
     * @throws invalid_argument si v no existe
     */
    AdysVal<Valor> const& adj(size_t v) const;
    
    /**
     * Muestra el grafo en el stream de salida o
     */
    void print(std::ostream& o = std::cout) const;
    
private:
    size_t _V;   // número de vértices
    size_t _E;   // número de aristas
    std::vector<AdysVal<Valor>> _adj;   // vector de listas de adyacentes
    
};

/**
 * Para mostrar grafos por la salida estándar.
 */
template <typename Valor>
std::ostream& operator<<(std::ostream & o, GrafoValorado<Valor> const& g);



// IMPLEMENTACIÓN

template <typename Valor>
Arista<Valor>::Arista()
: pimpl(nullptr) {}

template <typename Valor>
Arista<Valor>::Arista(size_t v, size_t w, Valor valor)
: pimpl(std::make_shared<Arista_impl<Valor>>(v, w, valor)) {}

template <typename Valor>
size_t Arista<Valor>::uno() const { return pimpl->uno(); }

template <typename Valor>
size_t Arista<Valor>::otro(size_t vert) const { return pimpl->otro(vert); }

template <typename Valor>
Valor Arista<Valor>::valor() const { return pimpl->valor(); }

template <typename Valor>
void Arista<Valor>::print(std::ostream & o) const { pimpl->print(o); }


template <typename Valor>
class Arista_impl {
public:
    Arista_impl(size_t v, size_t w, Valor valor) : v(v), w(w), _valor(valor) {};
    size_t uno() const { return v; }
    size_t otro(size_t vert) const { return (vert == v) ? w : v; }
    Valor valor() const { return _valor; }
    void print(std::ostream& o = std::cout) const {
        o << "(" << v << ", " << w << ", " << _valor << ")";
    }
private:
    size_t v, w;
    Valor _valor;
};


template <typename Valor>
void GrafoValorado<Valor>::ponArista(Arista<Valor> const& arista) {
    size_t v = arista.uno();
    size_t w = arista.otro(v);
    if (v >= _V || w >= _V) throw std::invalid_argument("Vertice inexistente");
    ++_E;
    _adj[v].push_back(arista);
    _adj[w].push_back(arista);
}

template <typename Valor>
AdysVal<Valor> const& GrafoValorado<Valor>::adj(size_t v) const {
    if (v >= _V) throw std::invalid_argument("Vertice inexistente");
    return _adj[v];
}

template <typename Valor>
void GrafoValorado<Valor>::print(std::ostream & o) const {
    o << _V << " vértices, " << _E << " aristas\n";
    for (auto v = 0; v < _V; ++v) {
        o << v << ": ";
        for (auto const& w : _adj[v]) {
            o << w << " ";
        }
        o << "\n";
    }
}

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, GrafoValorado<Valor> const& g){
    g.print(o);
    return o;
}


#endif /* GRAFOVALORADO_H_ */
