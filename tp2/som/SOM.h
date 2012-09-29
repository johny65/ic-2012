#ifndef _SOM_H_
#define _SOM_H_

#include <vector>
#include "Neurona.h"

using namespace std;
typedef vector< vector<Neurona> > Matriz;

class SOM {
private:
	double eta; ///< Tasa de aprendizaje
	Matriz grilla; ///< Grilla de neuronas
	int M, N; ///< Tamaño de la grilla
	vector< vector<double> > datos; ///< Entradas

	void inicializar_pesos();
	void competir(vector<double> &x, int &i, int &j);
	
public:
	SOM();
	~SOM();
	void verificar_inicializada();
	void inicializar(int, int);
	void entrenar(const char*);
};

#endif