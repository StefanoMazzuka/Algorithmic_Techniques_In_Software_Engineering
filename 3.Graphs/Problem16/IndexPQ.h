//
//  IndexPQ.h
//
//  Implementación de colas con prioridad mediante montículos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de un elemento puede ser modificada
//  con coste en O(log N).
//
//  Técnicas Algoritmicas en Ingeniería del Software / Diseño de Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef INDEXPQ_H_
#define INDEXPQ_H_

#include <iostream>
#include <stdexcept>
#include <vector>


// T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class IndexPQ {
public:
    // registro para las parejas < elem, prioridad >
    struct Par {
        size_t elem;
        T prioridad;
    };
    
    IndexPQ(size_t t, Comparator c = Comparator());
    
    IndexPQ(IndexPQ<T,Comparator> const&) = default;
    
//    IndexPQ(IndexPQ<T,Comparator> &&) = default;
    
    IndexPQ<T,Comparator>& operator=(IndexPQ<T,Comparator> const&) = default;
    
//    IndexPQ<T,Comparator>& operator=(IndexPQ<T,Comparator> &&) = default;
    
    ~IndexPQ() = default;
    
    // e debe ser uno de los posibles elementos
    void push(size_t e, T const& p);
    
    void update(size_t e, T const& p);
    
    bool empty() const { return (numElems == 0); }
    
    Par const& top() const;
    
    void pop();
    
    void print(std::ostream& o = std::cout) const;
    
    
private:
    /** Vector que contiene los datos (pares < elem, prio >). */
    std::vector<Par> array;     // primer elemento en la posición 1
    
    /** Vector que contiene las posiciones en array de los elementos. */
    std::vector<size_t> posiciones;   // un 0 indica que el elemento no está
    
    /** Número de elementos en el montículo. */
    size_t numElems;
    
    /** Objeto función que sabe comparar prioridades.
     * antes(a,b) es cierto si a es más prioritario que b
     */
    Comparator antes;
    
    void flotar(size_t n);
    
    void hundir(size_t n);
    
};


template <typename T, typename Comparator>
inline std::ostream& operator<<(std::ostream & o, IndexPQ<T,Comparator> const& a){
    a.print(o);
    return o;
}


template <typename T, typename Comparator>
IndexPQ<T,Comparator>::IndexPQ(size_t t, Comparator c) :
array(t+1), posiciones(t,0), numElems(0), antes(c) {};

template <typename T, typename Comparator>
void IndexPQ<T,Comparator>::push(size_t e, T const& p) {
    if (posiciones.at(e) != 0) throw std::invalid_argument("No se pueden insertar elementos repetidos.");
    else {
        ++numElems;
        array[numElems].elem = e; array[numElems].prioridad = p;
        posiciones[e] = numElems;
        flotar(numElems);
    }
}

template <typename T, typename Comparator>
void IndexPQ<T,Comparator>::update(size_t e, T const& p) {
    auto i = posiciones.at(e);
    if (i == 0) // el elemento e se inserta por primera vez
        push(e, p);
    else {
        array[i].prioridad = p;
        if (i != 1 && antes(array[i].prioridad, array[i/2].prioridad))
            flotar(i);
        else // puede hacer falta hundir a e
            hundir(i);
    }
}

template <typename T, typename Comparator>
typename IndexPQ<T,Comparator>::Par const& IndexPQ<T,Comparator>::top() const {
    if (numElems == 0) throw std::domain_error("No se puede consultar el primero de una cola vacía.");
    else return array[1];
}

template <typename T, typename Comparator>
void IndexPQ<T,Comparator>::pop() {
    if (numElems == 0) throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
    else {
        posiciones[array[1].elem] = 0; // para indicar que no está
        if (numElems > 1) {
            array[1] = std::move(array[numElems]);
            posiciones[array[1].elem] = 1;
            --numElems;
            hundir(1);
        } else
            --numElems;
    }
}

template <typename T, typename Comparator>
void IndexPQ<T,Comparator>::print(std::ostream& o) const {
    for (auto i = 1; i <= numElems; ++i)
        o << i << ":" << array[i].elem << "," << array[i].prioridad << " | ";
    std::cout << std::endl;
    for (auto i = 1; i < posiciones.size(); ++i)
        o << i << ":" << posiciones[i] << " | ";
    std::cout << std::endl;
}

template <typename T, typename Comparator>
void IndexPQ<T,Comparator>::flotar(size_t n) {
    Par parmov = std::move(array[n]);
    size_t hueco = n;
    while (hueco != 1 && antes(parmov.prioridad, array[hueco/2].prioridad)) {
        array[hueco] = std::move(array[hueco/2]); posiciones[array[hueco].elem] = hueco;
        hueco /= 2;
    }
    array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
}

template <typename T, typename Comparator>
void IndexPQ<T,Comparator>::hundir(size_t n) {
    Par parmov = std::move(array[n]);
    size_t hueco = n;
    size_t hijo = 2*hueco; // hijo izquierdo, si existe
    while (hijo <= numElems)  {
        // cambiar al hijo derecho de i si existe y va antes que el izquierdo
        if (hijo < numElems && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
            ++hijo;
        // flotar el hijo si va antes que el elemento hundiéndose
        if (antes(array[hijo].prioridad, parmov.prioridad)) {
            array[hueco] = std::move(array[hijo]); posiciones[array[hueco].elem] = hueco;
            hueco = hijo; hijo = 2*hueco;
        }
        else break;
    }
    array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
}


#endif /* INDEXPQ_H_ */
