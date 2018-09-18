//
//  Grafo.h
//
//  Implementación de grafos no dirigidos y clases que los exploran
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>


using Adys = std::vector<size_t>;  // lista de adyacentes a un vértice
using Path = std::deque<size_t>;   // para representar caminos

class Grafo {
    
    size_t _V;   // número de vértices
    size_t _E;   // número de aristas
    std::vector<Adys> _adj;   // vector de listas de adyacentes
    
public:
    
    /**
     * Crea un grafo con V vértices.
     */
    Grafo(size_t v) : _V(v), _E(0), _adj(_V) {}
    
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
    void ponArista(size_t v, size_t w) {
        if (v >= _V || w >= _V)
            throw std::invalid_argument("Vertice inexistente");
        ++_E;
        _adj[v].push_back(w);
        _adj[w].push_back(v);
    }
    
    
    /**
     * Devuelve la lista de adyacencia de v.
     * @throws invalid_argument si v no existe
     */
    const Adys& adj(size_t v) const {
        if (v >= _V)
            throw std::invalid_argument("Vertice inexistente");
        return _adj[v];
    }
    
    
    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream & o = std::cout) const {
        o << _V << " vértices, " << _E << " aristas\n";
        for (auto v = 0; v < _V; ++v) {
            o << v << ": ";
            for (auto w : _adj[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }
    
};

/**
 * Para mostrar grafos por la salida estándar.
 */
inline std::ostream& operator<<(std::ostream & o, Grafo const& g){
    g.print(o);
    return o;
}



/**
 * Recorrido en profundidad de un grafo a partir de un vértice origen.
 */
class DepthFirstSearch {
public:
    DepthFirstSearch(Grafo const& G, size_t s) : _count(0), _marked(G.V(), false) {
        dfs(G, s);
    }
    
    // ¿hay camino del origen a v?
    bool marked(size_t v) const {
        return _marked[v];
    }
    
    // número de vértices conectados a s (en la misma componente conexa que s)
    size_t count() const {
        return _count;
    }
    
private:
    std::vector<bool> _marked;  // marked[v] = ¿hay camino de s a v?
    size_t _count;              // número de vértices conectados a s
    
    // recorrido en profundidad desde v
    void dfs(Grafo const& G, size_t v) {
        ++_count;
        _marked[v] = true; // para no repetir vértices
        for (auto w : G.adj(v)) { // recorremos todos los adyacentes a v
            if (!_marked[w]) {
                dfs(G, w);
            }
        }
    }
    
};


/**
 * Recorrido en profundidad de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos desde el origen a todos los vértices alcanzables.
 */
class DepthFirstPaths {
public:
    DepthFirstPaths(Grafo const& G, size_t s) : marked(G.V(), false), edgeTo(G.V()), s(s) {
        dfs(G, s);
    }
    
    // ¿Hay camino del origen a v?
    bool hasPathTo(size_t v) const {
        return marked[v];
    }
    
    // Devuelve un camino desde el origen a v (vacío si no están conectados)
    Path pathTo(size_t v) const {
        Path path;
        if (!hasPathTo(v))
            return path;
        // recuperamos el camino retrocediendo
        for (auto x = v; x != s; x = edgeTo[x])
            path.push_front(x);
        path.push_front(s);
        return path;
    }
    
    
private:
    std::vector<bool> marked;    // marked[v] = ¿hay camino de s a v?
    std::vector<size_t> edgeTo;  // edgeTo[v] = último vértice antes de llegar a v
    size_t s;                    // vértice origen
    
    // recorrido en profundidad desde v
    void dfs(Grafo const& G, size_t v) {
        marked[v] = true;
        for (auto w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, w);
            }
        }
    }
};


/**
 * Recorrido en anchura de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos más cortos desde el origen a todos los vértices alcanzables.
 */
class BreadthFirstPaths {
public:
    BreadthFirstPaths(Grafo const& G, size_t s)
    : marked(G.V(), false), edgeTo(G.V()), distTo(G.V()), s(s) {
        bfs(G, s);
    }
    
    // ¿Hay camino del origen a v?
    bool hasPathTo(size_t v) const {
        return marked[v];
    }
    
    // Devuelve el camino más corto desde el origen a v (vacío si no están conectados)
    Path pathTo(size_t v) const {
        Path path;
        if (!hasPathTo(v))
            return path;
        // recuperamos el camino retrocediendo
        for (auto x = v; x != s; x = edgeTo[x])
            path.push_front(x);
        path.push_front(s);
        return path;
    }
    
    // Devuelve el número de aristas en el camino más corto a v
    size_t distance(size_t v) const {
        return distTo[v];
    }
    
private:
    std::vector<bool> marked;     // marked[v] = ¿hay camino de s a v?
    std::vector<size_t> edgeTo;   // edgeTo[v] = último vértice antes de llegar a v
    std::vector<size_t> distTo;   // distTo[v] = número de aristas en el camino s-v más corto
    size_t s;                     // vértice origen
    
    void bfs(Grafo const& G, size_t s) {
        std::queue<size_t> q;
        distTo[s] = 0;
        marked[s] = true;
        q.push(s);
        while (!q.empty()) {
            auto v = q.front(); q.pop();
            for (auto w : G.adj(v)) {
                if (!marked[w]) {
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
    }
    
};

#endif /* GRAFO_H_ */
