#ifndef SISTEMA_H
#define SISTEMA_H
#include "utils.h"
#include <vector>
using namespace std;

class Sistema {
private:
	vector<triangulo> conjuntos;
	
	//Variables y datos para la simulacion
	vector<double> temp_int; ///< temperatura interna: variable de salida 
	vector<double> temp_ext; ///< temperatura externa: fuera de la habitacion (entrada, aletoria)
	vector<double> i; ///<valor de la corriente para determinar el calor emitido por la resistencia que posee el calefactor (a controlar)
	vector<double> v; ///< valor del voltaje que recibe el refrigerador (a controlar)
	vector<double> temp_ref; ///< temperatura de referencia: variable a la que se debe ir ajustando la temp_int. (alterna entre 18 y 22 grados cada 10 minutos:600seg)
	
	
public:
	Sistema(int,vector<double>);
	~Sistema();
	void graficar_conjuntos();
	void Simular();
	void Fuzzification(); ///< convertir el universo de discurso X en el conjunto difuso A;
	void Defuzzification(); ///< convertir el conjunto difuso B al universo de discurso Y;
};

#endif

