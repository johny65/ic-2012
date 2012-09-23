#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Perceptron.h"
#include "rbf.h"
#include "utils.h"

using namespace std;


/**
 * @brief Clase Red Neuronal con Funciones de Base Radial (RBF-NN).
 *
 * Una Red Neuronal con Funciones de Base Radial (RBF-NN, Radial Basis Function
 * Neural Network) sólo contiene 2 capas de neuronas: una capa oculta donde
 * las neuronas poseen una función de base radial como función de activación,
 * y una capa de salidad con neuronas perceptrones simples (con una salida
 * lineal).
 * Esta red se entrena en 2 etapas: primero se entrenan las neuronas de la capa
 * oculta (se buscan los centros para las funciones de base radial) de una forma
 * no supervisada (mediante el algoritmo k-means). Después se entrenan las
 * neuronas de salida (sus pesos) mediante un método supervisado.
 * 
 */
class RBFNetwork {
private:

	double eta; ///< Tasa de aprendizaje
	int max_epocas; ///< Cantidad máxima de épocas
	double tol; ///< Tolerancia del error para detener el entrenamiento

	vector<Perceptron> capa_salida;
	vector<RBF> capa_oculta;
	
	vector< vector<double> > salidas_deseadas; ///< Vector con las salidas esperadas (en forma de vectores)
	vector< vector<double> > datos;
	vector< vector<double>* > salidas_capas; ///<es necesario guardar cada una de las salidas de las capas para hacer el paso hacia atras
	
	bool graficos; ///< Indica si se activan los gráficos o no
	bool couts; ///< Indica si se deben mostrar salidas por consola
	GNUplot plotter; ///< Conexión con GNUplot
	GNUplot error_graf; /// Para graficar error de entrenamiento

	vector< vector<double> > mapear(vector<double>&);
	void graficar_puntos(const char *archivo, const char *titulo);
	void verificar_inicializada();
	
public:

	RBFNetwork();
	~RBFNetwork();
	void setear_arquitectura(int unidades_ocultas, int unidades_salida);
	void set_max_epocas(int m);
	void set_tolerancia(double t);
	void set_tasa(double n);
	void entrenar(const char *name);
	void val_cross(const char *archivo, int k);
	double probar(const char *name);
	vector<double> clasificar(vector<double> &Datos);
	void guardar_pesos();
	void dibujar_red();
};

#endif
