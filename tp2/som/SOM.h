#ifndef _SOM_H_
#define _SOM_H_

#include <vector>
#include "Neurona.h"
#include "GNUplot.h"

using namespace std;
typedef vector< vector<Neurona> > Matriz;

class SOM {
private:
	double eta; ///< Tasa de aprendizaje inicial
	double t2; ///< Variable de tiempo para el cálculo de eta dinámico
	double sigma; ///< Sigma inicial para la función de vecindad
	double t; ///< Variable de tiempo para el cálculo de sigma dinámico
	double tol;
	Matriz grilla; ///< Grilla de neuronas
	int M, N; ///< Tamaño de la grilla
	vector< vector<double> > datos; ///< Entradas

	GNUplot plotter; ///< Conexión con GNUplot
	
	void verificar_inicializada();
	void inicializar_pesos();
	void competir(vector<double> &x, int &i, int &j);
	void actualizar_pesos(int iganadora, int jganadora, vector<double> &x, int n);
	void visualizar_resultados();
	void visualizar_datoslabel(int);

void display_cb();
	
public:
	SOM();
	~SOM();
	void set_tasa_inicial(double n);
	void set_t2(double t);
	void set_sigma_inicial(double s);
	void set_t(double t);
	void inicializar(int, int);
	void entrenar(const char*);
	vector<vector<peso_act> > generar_datos_grafico();
	
};

#endif
