#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include "GNUplot.h"

using namespace std;

class Perceptron;
typedef vector<Perceptron> Layer;

/**
 * @brief Clase Perceptron Simple
 */
class Perceptron {
private:
	int nd; ///< Cantidad total de entradas del perceptrón (incluye sesgo)
	vector<double> pesos; ///< Vector de pesos
	vector<double> dw_anteriores; ///< Vector de incrementos pasados de pesos, para usarlos con el término de momento
	double delta; ///< Gradiente local
	bool hidden; ///< Indica si pertenece a una capa oculta
	double v; ///< Campo inducido local (o salida lineal del perceptrón, es decir, v es igual a la suma de los pesos por las entradas sin pasar por la función de activación)

	
public:
	Perceptron();
	Perceptron(bool);
	~Perceptron();
	double get_delta();
	bool get_hidden();
	double get_salida();
	double get_peso(int peso);
	
	//void fijar_tasa(double m);
	//void set_tolerancia(double t);
	//void set_tiempo_espera(double t);
	//void set_graficos(bool g);
	//void set_show_error(bool g);
	//void set_salidas(bool s);
	
	void inicializar_pesos(int);
	double clasificar(const vector<double> &D);
	void calcular_delta(double ej);
	void calcular_delta(Layer&, int);
	void actualizar_pesos(vector<double> &ys, double e, double eta);
	void mostrar_pesos();
	vector<double>& get_vector_pesos();

};

#endif
