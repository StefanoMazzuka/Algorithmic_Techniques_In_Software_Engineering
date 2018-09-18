/*
 GRUPO:
 TAIS
 
 MIEMBROS:
 Stefano Mazzuka
 Silvia MartÌn
 */

#include<iostream>
#include<fstream>
#include<math.h>
#include"bintree_eda.h"

using namespace std;

// Lee un ·rbol binario de la entrada est·ndar
bintree<int> leerArbol(int vacio) {
    int raiz;
    cin >> raiz;
    if (raiz == vacio) return{}; // es un ·rbol vacÌo
    else { // leer recursivamente los hijos
        auto iz = leerArbol(vacio);
        auto dr = leerArbol(vacio);
        return{ iz, raiz, dr };
    }
}

/** Devuelve la altura del arbol en caso de ser AVL
 ** o -1 en caso de no serlo
 */
int esAVL(bintree<int> arbol, int maxN, int minN) {
    if (arbol.empty()) {
        return 0;
    }
    
    // Si la raiz se sale del rango de valores valido, el arbol no es AVL
    if (arbol.root() >= maxN || arbol.root() <= minN)  {
        return -1;
    }
    
    int alturaIz = esAVL(arbol.left(), arbol.root(), minN);
    // Si el hijo izquierdo no es AVL, el arbol no es AVL
    if (alturaIz == -1) {
        return -1;
    }
    int alturaDr = esAVL(arbol.right(), maxN, arbol.root());
    // Si el hijo derecho no es AVL, el arbol no es AVL
    if (alturaDr == -1) {
        return -1;
    }
    
    // Si la diferencia de altura de sus hijos es mayor a 1, el arbol no es AVL
    if (abs(alturaIz - alturaDr) > 1) {
        return -1;
    }
    
    // Devolvemos la mayor altura entre sus dos hijos mas el nodo actual
    return max(alturaIz, alturaDr) + 1;
}

void resuelveCaso() {
    bintree<int> arbol;
    arbol = leerArbol(-1);
    
    // Puede que haya que cambiar estos valores
    if (esAVL(arbol, 1000000000, -1) != -1) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos_2.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();
    // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
//    system("PAUSE");
#endif
    return 0;
}
