#include <iostream>
#include <valarray>
#include <vector>
#include <iterator>
#include "Perceptron.h"
//#include "func.h"

#include <ctime>
using namespace std;

// Qué es esto? Lo usamos para algo??

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
	//		v=(((95+rand()%(6))/100.0)*signo(-10+rand()%(21)));
			d.push_back(v);	
		}
		p.push_back(d);
		d.clear();
	}
	
	return p;
	
}

int main (int argc, char *argv[]) {
	Perceptron P;
	
//	if (argc == 2)
//		P.entrenar(argv[1]); //usa el primer parámetro como archivo de entrada
//	else
		P.entrenar("tabla_XOR.csv");
//	
	//P.probar("prueba.csv");
	//P.val_cross();

	cin.get();
	return 0;
}
