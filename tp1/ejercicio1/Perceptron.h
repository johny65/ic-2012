#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <valarray>
#include <vector>
#include "GNUplot.h"


using namespace std;

class Perceptron {
private:
	GNUplot plot;
	int nd; //numero de datos
	vector<double> pesos;
	vector<double> entradas;
	vector<double> salidas;
	double mu; //tasa de aprendizaje
	int func;
	
public:
	Perceptron(double t=0.05):mu(t){};
	Perceptron();
	~Perceptron();
	void entrenar(vector<vector<double> > &datos);
	void clasificar(vector<double> &datos);
	void sel_func(int x); //Selecciono la funcion 
	void fijar_tasa(double m);
	void result();
	void mostrar_pesos(); //muestra los pesos
	void graficar();
	
};

#endif

