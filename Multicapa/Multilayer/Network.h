#ifndef NETWORK_H
#define NETWORK_H


//#include "Layer.h"
//#include "armadillo"
#include <vector>
#include "Perceptron.h"
#include "utils.h"


using namespace std;

typedef vector<Perceptron> Layer;

/**
	@class Network se encarga de la comunicacion de las capas
*/

class Network {
private:
	vector<Layer> capas; /** R (capas) es el vector de capas, es decir la longitud del vector R determina la cantidad de capas en la red, siendo R[R.size()-1] la capa de salida*/
	vector<double> salidas_deseadas; ///< Vector con las salidas esperadas
	
	vector< vector<double> > datos;
	vector<Perceptron*> neuronas; ///< Vector con punteros a todos los perceptrones de la red
	int cant_clases;
	double eta; ///< Tasa de aprendizaje
	int max_iter; ///< Cantidad máxima de iteraciones
	//double (*func)(double, double); ///< Función de activación
	double tol; ///< Tolerancia del error para detener el entrenamiento
	bool graficos; ///< Indica si se activan los gráficos o no
	bool couts; ///< Indica si se deben mostrar salidas por consola
	bool show_error; ///< Indica si se debe mostrar el gráfico de error
	GNUplot plotter; ///< Conexión con GNUplot


	vector< vector<double> > mapear(vector<double>&);
	void inicializar_pesos();
	void graficar_puntos(const char *archivo, const char *titulo);
	
	//Col <double> Datos;
	//Col <double> d;///< salida esperada para cada fila de la matrix Datos;
public:
	//Setear_arquitectura()  (idea funcion que setee las conexiones de las capas todos contra todos o como sea)
	Network(vector<double> perceptrones_por_capa);
	~Network();
	
	int cant_capas();
	void entrenar(const char *name);
	void val_cross(const char *ruta);
	void probar(const char *name);
	//Col <double> clasificar(); //el dense_vector de salida contiene 1 solo elemento en caso que en la capa de salida solo exista una sola neurona
	
};

#endif

