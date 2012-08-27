#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include "GNUplot.h"

using namespace std;

class Perceptron {
	/**
	@brief Clase Perceptron Simple
	*/
private:
	GNUplot plotter;
	int nd; //numero de datos ¿?
	int epocas;
	vector<double> pesos;
	vector<double> entradas;
	vector<double> salidas;
	vector<double> salidas_deseadas;
	double eta; //tasa de aprendizaje
	double (*func)(double, double);
	int max_iter;
	double tol; //tolerancia de corte
	void armar_recta(vector<double>&);
	
public:
	Perceptron(double);
	Perceptron();
	~Perceptron();
	void def_epocas(int g);
	void entrenar(const char *name);
	void probar(const char *name);
	double clasificar(vector<double> &datos);
	void sel_func(int x); //Selecciono la funcion 
	void fijar_tasa(double m);
	void result();
	void mostrar_pesos(); //muestra los pesos
	void graficar();
	
};

#endif
