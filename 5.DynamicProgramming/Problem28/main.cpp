/*
GRUPO:
TAIS 26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include"Matriz.h"
#include <algorithm>

using namespace std;


/*
	CASO RECURSIVO:

		i:cofre
		j:tiempo

		Casos base:
			tesoro (0,j); = 0
			tesoro (i,0); = 0

		Caso recursivo:
			tesoro(i-1,j);				si			   vCofres[i].p * 3 > j
			max(tesoro(i-1,j), tesoro(i-1,j - (cofre[i].p*3) + cofre[i].o));

	Coste: O(N*M) en recorrer la matriz donde N es el numero de cofres que vamso abuscar
	 y M el tiempo del que disponemso para ir a buscarlos.
*/
struct tCofre {
	int p;
	int o;
};

/*
	PARAMETROS:
	vCofres:
	teimpo:
	elegidos:
	maxOro:
	recogidos:
*/
void tesoro(vector<tCofre>const& vCofres, int tiempo,  vector<bool>& elegidos, int& maxOro, int& recogidos ) {

	int row = vCofres.size()-1; 
	int col = tiempo; 

	//creamos la matriz de solucion, inicializada a 0 (no tenemos ningun cofre recogido)
	//añadiendo una fila y comluna de mas para poder comparar
	Matriz<int> mochila(row+1, col+1, 0);
	
	for (size_t i = 1; i <= row; i++){ //recorremos los cofres
		
		for (size_t j = 1; j <= tiempo; j++){ //tiempo disponible

			/*
				comprobamos si hay suficiente en la botella para bajar a recoger el cofre actual
				si no lo hubiera directamente no entramos a los casos ´recursivos´
				lo multiplicamos por 3 porque es
				p para bajar y 2p para subir
			*/

			//si el tiempo que tardo en coger el cofre se pasa del disponible (nos quedamos con el antrior)
			if ( vCofres[i].p * 3 > j)
				mochila[i][j] = mochila[i-1][j];
			else //el maximo entre no coger el cofre actual o cogerlo (p*3 lo que nos cuesta bajar a por el)
				mochila[i][j] = max( mochila[i-1][j], mochila[i-1][j - (vCofres[i].p * 3)] + vCofres[i].o);
		}
	}//for row

	//solucion final
	maxOro = mochila[row][col];


	//vemos cuales han sido los cofres elegidos para recogerse
	int resto = tiempo;

	//vemos los cofres que hemso decidido coger
	for (size_t i = row; i >=1; i--){

		//si en la posicion de mi cofre con el timpo disponible es igual al cofre anteriro
		//significa que no lo cogimos (no me joramos la solucion) por eso es igual
		if (mochila[i][resto] == mochila[i - 1][resto])
			elegidos[i] = false;

		else { //actualizamos el tiempo que nos queda tras haer cogido el cofre
			elegidos[i] = true;
			resto -= (vCofres[i].p * 3);
			recogidos++;
		}
	}//for

}//recoger tesoro

bool resuelveCaso() {
	
	int tiempoBotella, numCofres;
	cin >> tiempoBotella >> numCofres;

	if (!cin)
		return false;

	//aumentamos en uno para que no nos cuente la pos 0
	vector<tCofre> vCofres(numCofres + 1);

	for (size_t i = 1; i <= numCofres; i++){
		cin >> vCofres[i].p  >> vCofres[i].o;
	}

	//vector<int> elegidos(numCofres + 1);

	vector<bool> elegidos(numCofres + 1);
	int oroTotal = 0, recogidos = 0;

	tesoro(vCofres,tiempoBotella,elegidos,oroTotal,recogidos);

	cout << oroTotal << endl;
	cout << recogidos << endl;

	for (int i = 1; i <= numCofres; i++) {
		if (elegidos[i])
			cout << vCofres[i].p << " " << vCofres[i].o << endl;
	}
	cout << "----" << endl;

	return true;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	
	while (resuelveCaso());

	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}