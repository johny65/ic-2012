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
	int nd; ///< Cantidad total de entradas del perceptrón (incluye sesgo)
	vector<double> pesos; ///< Vector de pesos
	vector<double> salidas; ///< Vector de salidas
	vector<double> salidas_deseadas; ///< Vector con las salidas esperadas
	double eta; ///< Tasa de aprendizaje
	int max_iter; ///< Cantidad máxima de iteraciones
	double (*func)(double, double); ///< Función de activación
	double tol; ///< Tolerancia del error para detener el entrenamiento
	bool graficos; ///< Indica si se activan los gráficos o no
	bool couts; ///< Indica si se deben mostrar salidas por consola
	vector<double> error; //por epoca
	vector<vector<double> > weight;

	GNUplot plotter; ///< Conexión con GNUplot
	double tiempo_espera; ///< Tiempo entre frames para la animación
	void graficar(const char *titulo);
	void graficar();
	
public:
	Perceptron();
	~Perceptron();
	void fijar_tasa(double m);
	void set_iteraciones_max(int m);
	void set_tolerancia(double t);
	void set_tiempo_espera(double t);
	void set_graficos(bool g);
	void set_salidas(bool s);
	int entrenar(const char *name);
	void probar(const char *name);
	double clasificar(const vector<double> &D);
	void sel_func(int x); //Selecciono la funcion 
	void val_cross(const char *ruta);
	void result();
	void mostrar_pesos(); //muestra los pesos

	
};

#endif


