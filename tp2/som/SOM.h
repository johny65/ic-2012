#ifndef _SOM_H_
#define _SOM_H_

#include <vector>
#include "Neurona.h"

using namespace std;
typedef vector< vector<Neurona> > Matriz;

class SOM {
private:
	double eta; ///< Tasa de aprendizaje
	///\todo hacer eta variable con el tiempo
	double sigma; ///< Sigma inicial para la función de vecindad
	double t; ///< Variable de tiempo para el cálculo de sigma dinámico
	Matriz grilla; ///< Grilla de neuronas
	int M, N; ///< Tamaño de la grilla
	vector< vector<double> > datos; ///< Entradas

	void inicializar_pesos();
	void competir(vector<double> &x, int &i, int &j);
	void actualizar_pesos(int iganadora, int jganadora, vector<double> &x, int n);
	
public:
	SOM();
	~SOM();
	void set_tasa(double n);
	void set_sigma(double s);
	void set_t(double t);
	void verificar_inicializada();
	void inicializar(int, int);
	void entrenar(const char*);
};

#endif