#ifndef SISTEMA_H
#define SISTEMA_H
#include "utils.h"
#include <vector>
#include "GNUplot.h"
using namespace std;

class Sistema {
private:
	vector<triangulo> conjuntos;
	
	//Variables y datos para la simulacion
	vector<double> temp_int_sc; ///< temperatura interna simulada sin control: variable de salida
	vector<double> temp_int_cc; ///< temperatura interna simulada con control
	vector<double> temp_ext; ///< temperatura externa: fuera de la habitacion (entrada, aletoria)
	vector<double> i; ///<valor de la corriente para determinar el calor emitido por la resistencia que posee el calefactor (a controlar)
	vector<double> v; ///< valor del voltaje que recibe el refrigerador (a controlar)
	vector<double> temp_ref; ///< temperatura de referencia: variable a la que se debe ir ajustando la temp_int. (alterna entre 18 y 22 grados cada 10 minutos:600seg)
	
	
	bool puerta_abierta; ///< es true cuando la puerta esta abierta false en caso contrario (si la puerta esta abierta en 10s se cierra)
	GNUplot plotter;
	
	//funciones privadas
	void graficar_conjuntos();
	void graficar(vector<double> &T);
public:
	Sistema(int, vector<double>); ///< cant_conjuntos: cant de triangulos borrosos, min: rango de temp minimo, max:rango de tem maximo
	~Sistema();
	
	void Simular_sincontrol();
	void Simular_concontrol();
	void Fuzzification(); ///< convertir el universo de discurso X en el conjunto difuso A;
	void Defuzzification(); ///< convertir el conjunto difuso B al universo de discurso Y;

};

#endif

