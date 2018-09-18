/*
	Grupo TAIS26 Silvia y Stefano

	solución al problema 02 donde indicamos si el arbol esta 
	equilibrado y es binario de busqueda
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

// lee un árbol binario de la entrada estándar
template <typename T>
bintree<T> leerArbol(T vacio) {
	T raiz;
	std::cin >> raiz;

	if (raiz == vacio) { // es un árbol vacío
		return {};

	} else { // leer recursivamente los hijos

		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);

		return {iz, raiz, dr};
	}
}

/*
	dado un árbol binario, calcula su altura
	el coste es lineal O(n) donde n es el número de nodos del árbol
*/
unsigned int altura(bintree<int> const& arbol) {
	if (arbol.empty()) //caso base si el árbol es vacio
		return 0;
	else
		return 1 + max(altura(arbol.left()), altura(arbol.right()));

	//cogemos el máximo de nodos entre la parte izquierda y derecha del arbol
}

/*
	dado el arbol creado lo recorremo sen inorden
	y teien que segui la siguiente forma menor medio mayor
	cada tres posiciones si no lo cumple es que no es un arbol de busqueda
	ya que hi menor que raiz y hd mayor que raiz
	el coste es O(n) siendo n los nodos que hay en el arbol
	porque tiene que recorrerse todos los nodos del arbol
*/
bool binario(bintree<int> const& arbol) {

	if (arbol.empty()) //caso base si el árbol es vacio
		return true;
	
	auto v = arbol.inorder();
	int tam = v.size();
	int i = 0;

	while(i < tam-1){

		if ( (v[i] < v[i + 1]))
			i++;
		else
			return  false;
	}

	return true;
}

/*
	dado un árbol binario, calcula si está equilibrado
	si es vacio está equilibrado
	calculamos la altura de los hijos de la izquierda y derecha
	si es <=1 seguimos viendo si el resto del arbol es equilibrado sino termianmos

	el coste es lineal O(n) donde n es el número de nodos del árbol
	que recorremos cuando calculamos la altura del árbol
*/
bool equilibrado(bintree<int> const& arbol) {

	 if (arbol.empty()) //caso base si el árbol es vacio
		 return true;
	 else{

		 //calculamos la altura de los hijos IZ y DR de un padre y luego hacemos la
		 //diferencia entre alturas
		 int alt = altura(arbol.left()) - altura(arbol.right());

		 //vemos si la diferencia es <=1 para que sea equilibrado
		 //y lo comprobamos tambien con sus hijos que ambos deben cumplirse
		 if (abs(alt) <= 1 && equilibrado(arbol.left()) && equilibrado(arbol.right()))
			 return true;
		 else
			 return false;
	 }
}

// resolvemos cada caso de prueba
void resuelveCaso() {
	auto arbol = leerArbol(-1);

	if (equilibrado(arbol) && binario(arbol))
		std::cout << "SI" << "\n";
	else
		std::cout << "NO" << "\n";
}

int main() {

// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
		std::ifstream in("casos.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
	#endif

	int numCasos;
	std::cin >> numCasos;

	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
	#ifndef DOMJUDGE
		std::cin.rdbuf(cinbuf);
		system("PAUSE");
	#endif

	return 0;
}
