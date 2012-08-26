#include <iostream>
#include <valarray>
#include <vector>
#include <iterator>
#include "Perceptron.h"

using namespace std;

int sign(int x){
	if(x>=0) return 1;
	else return -1;
}

vector<vector<double> > generar_datprueba(double porc, int l){
	/**
		@brief genera una matriz con datos para realizar las pruebas (ejercicio 1: OR o XOR)
		@param porc es el % de desvio de los datos
		@param l cantidad de datos a generar
	*/
	vector<vector<double> > p;
	vector<double> d;
	double v;
	srand(time(NULL));
	for(int i=0;i<l;i++){
		for(int j=0;j<2;j++){ //solo genero las entradas no las salidas esperadas
			v=(((95+rand()%(6))/100.0)*sign(-10+rand()%(21)));
			d.push_back(v);	
		}
		p.push_back(d);
		d.clear();
	}
	
	return p;
	
}

int main (int argc, char *argv[]) {
	Perceptron P(0.005);
	
	if (argc == 2)
		P.entrenar(argv[1]); //usa el primer parámetro como archivo de entrada
	else
		P.entrenar("datos.csv");
	
	P.probar("prueba.csv");
	
	return 0;
}
