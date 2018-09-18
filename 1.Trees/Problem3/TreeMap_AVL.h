//
//  TreeMap_AVL.h
//
//  Implementación de diccionarios <clave, valor> como árboles de búsqueda AVL
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 16/6/17.
//  Copyright (c) 2017 Alberto Verdejo. All rights reserved.
//

#ifndef TREEMAP_AVL_H_
#define TREEMAP_AVL_H_

#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <type_traits>  // std::conditional

using namespace std;

template <class Clave, class Valor, class Comparador = std::less<Clave>>
class map {
public:
	// parejas (clave, valor)
	struct clave_valor {
		const Clave clave;
		Valor valor;
		clave_valor(Clave const& c, Valor const& v = Valor()) : clave(c), valor(v) {};
	};
protected:
	using map_t = map<Clave, Valor, Comparador>;

	/*
	 Clase nodo que almacena internamente la pareja (clave, valor),
	 punteros al hijo izquierdo y al hijo derecho, y la altura.
	 */
	struct TreeNode;
	using Link = TreeNode *;
	struct TreeNode {
		clave_valor cv;
		Link iz;
		Link dr;
		size_t altura;
		TreeNode(clave_valor const& e, Link i = nullptr, Link d = nullptr,
			int alt = 1) : cv(e), iz(i), dr(d), altura(alt) {}
	};

	// puntero a la raíz de la estructura jerárquica de nodos
	Link raiz;

	// número de parejas <clave, valor>
	size_t nelems;

	// objeto función que compara elementos
	Comparador menor;

public:

	map(Comparador c = Comparador()) : raiz(nullptr), nelems(0), menor(c) {}

	map(map_t const& other) {
		raiz = copia(other.raiz);
		nelems = other.nelems;
		menor = other.menor;
	}

	map_t & operator=(map_t const& that) {
		if (this != &that) {
			libera(raiz);
			raiz = copia(that.raiz);
			nelems = that.nelems;
			menor = that.menor;
		}
		return *this;
	}

	~map() {
		libera(raiz);
		raiz = nullptr;
	};

	void insert(clave_valor const& cv) {
		inserta(cv, raiz);
	}

	bool empty() const {
		return raiz == nullptr;
	}

	size_t size() const {
		return nelems;
	}

	bool contains(Clave const& c) const {
		return busca(c, raiz) != nullptr;
	}

	Valor const& at(Clave const& c) const {
		Link p = busca(c, raiz);
		if (p == nullptr)
			throw std::out_of_range("La clave no se puede consultar");
		return p->cv.valor;
	}

	Valor & operator[](Clave const& c) {
		return corchete(c, raiz);
	}

	void erase(Clave const& c) {
		borra(c, raiz);
	}

	// solo para depurar (gira la cabeza)
	void print(std::ostream& o = std::cout) const {
		if (raiz != nullptr) {
			print(o, 0, raiz);
		}
		else
			o << "vacio\n";
	}

	void rango(map<int, int> const& arbol, int k1, int k2) {

		rangoAux(arbol.raiz, k1, k2);

		std::cout << "\n";

	}

	void rangoAux(Link a, int k1, int k2) {

		if (a != nullptr) {

			int elem = a->cv.clave;

			if (elem < k1)
				rangoAux(a->dr, k1, k2);

			else {
				rangoAux(a->iz, k1, k2);

				if (elem >= k1 && elem <= k2)
					cout <<elem << " ";

				if (elem < k2)
					rangoAux(a->dr, k1, k2);
					
			}
			
		}//arbol != NULL

	}//rangoAux

protected:

	static Link copia(Link a) {
		if (a == nullptr) return nullptr;
		else return new TreeNode(a->cv, copia(a->iz), copia(a->dr));
	}

	static void libera(Link a) {
		if (a != nullptr) {
			libera(a->iz);
			libera(a->dr);
			delete a;
		}
	}

	Link busca(Clave const& c, Link a) const {
		if (a == nullptr) {
			return nullptr;
		}
		else if (menor(c, a->cv.clave)) {
			return busca(c, a->iz);
		}
		else if (menor(a->cv.clave, c)) {
			return busca(c, a->dr);
		}
		else { // c == a->cv.clave
			return a;
		}
	}

	void inserta(clave_valor const& cv, Link & a) {
		if (a == nullptr) {
			a = new TreeNode(cv);
			++nelems;
		}
		else if (menor(cv.clave, a->cv.clave)) {
			inserta(cv, a->iz);
			reequilibraDer(a);
		}
		else if (menor(a->cv.clave, cv.clave)) {
			inserta(cv, a->dr);
			reequilibraIzq(a);
		}
		else { // la clave ya está, se actualiza el valor asociado
			a->cv.valor = cv.valor;
		}
	}

	Valor & corchete(Clave const& c, Link & a) {
		if (a == nullptr) {
			a = new TreeNode(clave_valor(c));
			++nelems;
			return a->cv.valor;
		}
		else if (menor(c, a->cv.clave)) {
			Valor & v = corchete(c, a->iz);
			reequilibraDer(a);
			return v;
		}
		else if (menor(a->cv.clave, c)) {
			Valor & v = corchete(c, a->dr);
			reequilibraIzq(a);
			return v;
		}
		else { // la clave ya está, se devuelve el valor asociado
			return a->cv.valor;
		}
	}

	static size_t altura(Link a) {
		if (a == nullptr) return 0;
		else return a->altura;
	}

	static void rotaDer(Link & k2) {
		Link k1 = k2->iz;
		k2->iz = k1->dr;
		k1->dr = k2;
		k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
		k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
		k2 = k1;
	}

	static void rotaIzq(Link & k1) {
		Link k2 = k1->dr;
		k1->dr = k2->iz;
		k2->iz = k1;
		k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
		k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
		k1 = k2;
	}

	static void rotaIzqDer(Link & k3) {
		rotaIzq(k3->iz);
		rotaDer(k3);
	}

	static void rotaDerIzq(Link & k1) {
		rotaDer(k1->dr);
		rotaIzq(k1);
	}

	static void reequilibraIzq(Link & a) {
		if (altura(a->dr) - altura(a->iz) > 1) {
			if (altura(a->dr->iz) > altura(a->dr->dr))
				rotaDerIzq(a);
			else rotaIzq(a);
		}
		else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
	}

	static void reequilibraDer(Link & a) {
		if (altura(a->iz) - altura(a->dr) > 1) {
			if (altura(a->iz->dr) > altura(a->iz->iz))
				rotaIzqDer(a);
			else rotaDer(a);
		}
		else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
	}

	void borra(Clave const& c, Link & a) {
		if (a != nullptr) {
			if (menor(c, a->cv.clave)) {
				borra(c, a->iz);
				reequilibraIzq(a);
			}
			else if (menor(a->cv.clave, c)) {
				borra(c, a->dr);
				reequilibraDer(a);
			}
			else // c == a->cv.clave
				if (a->iz == nullptr || a->dr == nullptr) {
					Link aux = a;
					a = a->iz == nullptr ? a->dr : a->iz;
					--nelems;
					delete aux;
				}
				else { // tiene dos hijos
					subirMenor(a, a->dr, nullptr);
					--nelems;
				}
		}
	}

	static void subirMenor(Link & a, Link b, Link padre) {
		if (b->iz != nullptr) {
			subirMenor(a, b->iz, b);
			reequilibraIzq(b);
		}
		else {
			if (padre != nullptr) {
				padre->iz = b->dr;
				b->dr = a->dr;
			}
			b->iz = a->iz;
			delete a;
			a = b;
			a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
		}
	}

	// imprime el árbol (solo para depurar)
	static void print(std::ostream & o, int indent, Link r) {
		if (r != nullptr) {
			print(o, indent + 2, r->dr);
			o << std::string(indent, ' ');
			o << '(' << r->cv.clave << ',' << r->cv.valor << ")\n";
			print(o, indent + 2, r->iz);
		}
	}

protected:
	// iteradores que recorren los pares <clave, valor> de menor a mayor clave
	template <bool is_const>
	class Iterador {
		using reference = typename std::conditional<is_const, clave_valor const&, clave_valor &>::type;
		using pointer = typename std::conditional<is_const, clave_valor const*, clave_valor *>::type;

	public:
		reference operator*() const {
			if (act == nullptr) throw std::out_of_range("No hay elemento a consultar");
			return act->cv;
		}

		pointer operator->() const {
			return &operator*();
		}

		Iterador & operator++() {  // ++ prefijo
			next();
			return *this;
		}

		bool operator==(Iterador const& that) const {
			return act == that.act;
		}
		bool operator!=(Iterador const& that) const {
			return !(this->operator==(that));
		}

	protected:
		friend class map;
		Link act;
		std::stack<Link> ancestros;  // antecesores no visitados

		// construye el iterador al primero
		Iterador(Link r) { act = first(r); }

		// construye el iterador al último
		Iterador() : act(nullptr) {}

		// construye el iterador a una clave concreta (para find)
		Iterador(map_t const* m, Clave const& c) {
			act = m->raiz;
			bool encontrado = false;
			while (act != nullptr && !encontrado) {
				if (m->menor(c, act->cv.clave)) {
					ancestros.push(act);
					act = act->iz;
				}
				else if (m->menor(act->cv.clave, c)) {
					act = act->dr;
				}
				else
					encontrado = true;
			}
			if (!encontrado) { // vaciamos la pila
				ancestros = std::stack<Link>();
			}
		}

		Link first(Link ptr) {
			if (ptr == nullptr) {
				return nullptr;
			}
			else { // buscamos el nodo más a la izquierda
				while (ptr->iz != nullptr) {
					ancestros.push(ptr);
					ptr = ptr->iz;
				}
				return ptr;
			}
		}

		void next() {
			if (act == nullptr) {
				throw std::out_of_range("El iterador no puede avanzar");
			}
			else if (act->dr != nullptr) { // primero del hijo derecho
				act = first(act->dr);
			}
			else if (ancestros.empty()) { // hemos llegado al final
				act = nullptr;
			}
			else { // podemos retroceder
				act = ancestros.top();
				ancestros.pop();
			}
		}
	};

public:
	// iterador que no permite modificar el elemento apuntado
	using const_iterator = Iterador<true>;

	const_iterator cbegin() const {
		return const_iterator(raiz);
	}
	const_iterator begin() const {
		return cbegin();
	}

	const_iterator cend() const {
		return const_iterator();
	}
	const_iterator end() const {
		return cend();
	}

	const_iterator find(Clave const& c) const {
		return const_iterator(this, c);
	}

	// iterador que sí permite modificar el elemento apuntado (su valor)
	using iterator = Iterador<false>;

	iterator begin() {
		return iterator(raiz);
	}

	iterator end() {
		return iterator();
	}

	iterator find(Clave const& c) {
		return iterator(this, c);
	}

};


template <class Clave, class Valor, class Comparador>
inline std::ostream& operator<<(std::ostream & o, map<Clave, Valor, Comparador> const& a) {
	a.print(o);
	return o;
}

#endif // treemap_eda_h
