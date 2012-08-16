#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <valarray>

using namespace std;

class Perceptron {
private:
	
	valarray<double> pesos;
	valarray<double> entradas;
	double mu; //tasa de aprendizaje
	
	
public:
	Perceptron();
	~Perceptron();
	
	void cargar_datos();
	void entrenar();
	void clasificar();
	
};

#endif

