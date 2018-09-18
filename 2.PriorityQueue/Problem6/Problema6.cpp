/*
GRUPO:
TAIS26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include"PriorityQueue.h"

using namespace std;

struct tUsuario {
	int ID;
	int periodo;
	int siguienteEnvio;
	bool operator<(tUsuario otro) const {
		return siguienteEnvio < otro.siguienteEnvio || 
			siguienteEnvio == otro.siguienteEnvio && ID < otro.ID;
	}
};

PriorityQueue<tUsuario> leerUsuarios(int numUsuarios) {
	PriorityQueue<tUsuario> listaUsuarios;

	for (int i = 0; i < numUsuarios; i++) {
		tUsuario usuario;
		cin >> usuario.ID;
		cin >> usuario.periodo;
		usuario.siguienteEnvio = usuario.periodo;
		listaUsuarios.push(usuario);
	}

	return listaUsuarios;
}

// COSTE: 
void resuelveCaso(int numUsuarios) {
	PriorityQueue<tUsuario> listaUsuarios = leerUsuarios(numUsuarios);
	int numEnvios;

	cin >> numEnvios;

	for (int i = 0; i < numEnvios; i++) {
		tUsuario usuario = listaUsuarios.top();
		listaUsuarios.pop();
		cout << usuario.ID << endl;
		usuario.siguienteEnvio += usuario.periodo;
		listaUsuarios.push(usuario);
	}
	cout << "----" << endl;
}

int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_6.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int numUsuarios;
	cin >> numUsuarios;
	while (numUsuarios > 0) {
		resuelveCaso(numUsuarios);
		cin >> numUsuarios;
	}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}