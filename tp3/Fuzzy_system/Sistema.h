#ifndef SISTEMA_H
#define SISTEMA_H

#include <map>
#include <vector>
#include "utils.h"
#include "GNUplot.h"

using namespace std;

//#define MUYPOCA 0
#define POCA 0
#define MEDIANA 1
#define MUCHA 2
#define MUCHISIMA 3

#define BAJA 0
#define MEDIA 1
#define ALTA 2

#define MUYPOCO 0
#define POCO 1
#define MEDIO 2
#define ALTO 3
#define MUYALTO 4


class Sistema {
private:
	vector<triangulo> conjuntos_i; ///< conjuntos pertenecientes a la corriente i
	vector<triangulo> conjuntos_v; ///< conjuntos pertenecientes al voltaje v

	vector<triangulo> conjuntos_te;
	vector<triangulo> conjuntos_var;
	
	//Variables y datos para la simulacion
	vector<double> temp_int_sc; ///< temperatura interna simulada sin control: variable de salida
	vector<double> temp_int_cc; ///< temperatura interna simulada con control
	vector<double> temp_ext; ///< temperatura externa: fuera de la habitacion (entrada, aleatoria)
	vector<double> i; ///<valor de la corriente para determinar el calor emitido por la resistencia que posee el calefactor (a controlar)
	vector<double> v; ///< valor del voltaje que recibe el refrigerador (a controlar)
	vector<double> temp_ref; ///< temperatura de referencia: variable a la que se debe ir ajustando la temp_int. (alterna entre 18 y 22 grados cada 10 minutos:600seg)
	
	int puerta_abierta; ///< Indica el instante de tiempo cuando la puerta está abierta
	GNUplot plotter, plotter_t, plotter_i, plotter_v, plotter_var;
	
	//funciones privadas
	void graficar(vector<double> &T);
	void graficar_controlado();
	void graficar_historia(vector<double> &n, vector<double> &i, vector<double> &v);
	trapezoide verificar_regla(int A1, int A2, int C, char c, double a1, double a2);
	double Defuzzification(vector<trapezoide> &v); ///< convertir el conjunto difuso B al universo de discurso Y;
	void regla_corriente(int A1, int A2, int C, double a1, double a2, vector<trapezoide> &v);
	void regla_voltaje(int A1, int A2, int C, double te, double var,	vector<trapezoide> &v);
	void set_conjuntos(vector<double> &te, vector<double> &var);

public:
	Sistema(vector<double>&, vector<double>&, vector<double>&, vector<double>&); ///< cant_conjuntos: cant de triangulos borrosos, min: rango de temp minimo, max:rango de tem maximo
	~Sistema();
	void graficar_conjuntos();
	void Simular_sincontrol();
	void Simular_concontrol();

};

#endif
