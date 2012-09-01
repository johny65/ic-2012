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
	vector<double> error; //por epoca
	vector<vector<double> > weight;
	double eta; //tasa de aprendizaje
	double (*func)(double, double);
	int max_iter;
	double tol; //tolerancia de corte
	void graficar(vector<double> &pesos);
	
public:
	Perceptron(double);
	Perceptron();
	~Perceptron();
	void def_epocas(int g);
	int entrenar(const char *name);
	void probar(const char *name);
	double clasificar(vector<double> &datos);
	void sel_func(int x); //Selecciono la funcion 
	void fijar_tasa(double m);
	void val_cross();
	void result();
	void particionar(int cant, float porc);
	void mostrar_pesos(); //muestra los pesos

	
};

#endif


