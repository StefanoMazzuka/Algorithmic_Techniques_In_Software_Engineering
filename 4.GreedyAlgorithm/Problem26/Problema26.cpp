/*
GRUPO:
TAIS 26

MIEMBROS:
Stefano Mazzuka
Silvia Martín
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

struct tTrabajo
{
	int comienzo;
	int fin;
};

bool comparador(const tTrabajo& A, const tTrabajo& B) {
	return (A.comienzo < B.comienzo) || (A.comienzo == B.comienzo && A.fin < B.fin);
}

// COSTE: O(N) Siendo N el num de trabajos.
bool resuelveCaso() {
	int C, F, N;
	cin >> C >> F >> N;
	if (C == 0 && F == 0 && N == 0) return false;

	// Leemos los trabajos y busco el trabajo inicial//
	vector<tTrabajo> trabajos(N);
	tTrabajo trabajo;
	int finalMaximo = 0, trabajoInicial = -1;
	for (int i = 0; i < N; i++) {
		cin >> trabajo.comienzo >> trabajo.fin;
		trabajos[i] = trabajo;
	}

	sort(trabajos.begin(), trabajos.end(), comparador);

	for (int i = 0; i < N; i++) {
		if (trabajos[i].comienzo <= C && trabajos[i].fin > finalMaximo) {
			finalMaximo = trabajos[i].fin;
			trabajoInicial = i;
		}
	}

	// Compruebo que no hay un trabajo inicial //
	if (trabajoInicial == -1) {
		cout << "Imposible" << endl;
		return true;
	}

	tTrabajo trabajoBase = trabajos[trabajoInicial], trabajoCandidato = trabajoBase;
	int numTrabajos = 1, i = trabajoInicial + 1;
	bool imposible = false;
	finalMaximo = trabajoBase.fin;
	while (i < N && finalMaximo < F) {
		if (trabajos[i].comienzo > trabajoBase.fin) {
			i = N;
			imposible = true;
		}
		else {
			while (i < N && trabajos[i].comienzo <= trabajoBase.fin) {
				if (trabajos[i].fin > finalMaximo) {
					trabajoCandidato = trabajos[i];
					finalMaximo = trabajos[i].fin;
				}
				i++;
			}
			trabajoBase = trabajoCandidato;
			numTrabajos++;
		}
	}

	if (trabajoBase.fin < F) imposible = true;

	if (imposible) cout << "Imposible" << endl;
	else cout << numTrabajos << endl;

	return true;
}
int main() {
	// Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos_26.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso()) {}
	// Para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}