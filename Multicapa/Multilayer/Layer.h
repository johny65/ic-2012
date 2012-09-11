#ifndef LAYER_H
#define LAYER_H
#include "armadillo"

 
#include <vector>
#include "Perceptron.h"
using namespace std;
using namespace arma;


class Layer {
private:
	
	vector<Perceptron> capa;
	int id; /** identifica la capa (capa numero 1,2, etc)*/
	int NP; /**NP numero de perceptrones por capa (este numero sera igual al numero de filas de la matriz M)*/
	
	bool hidden; /**hidden=True la capa es oculta, caso contrario es la capa de salida*/
//	
//	mat M; /**M matriz correspondiente a la capa id en cada fila i tiene los pesos correspondiente al i-esimo perceptron contenido en ella*/
//	Col <double> x; /**x es el vector de entradas con sesgo incluido*/	
//	Col <double> y; /**y es el vector de salidas para la capa en cuestion, el emento y[0] corresponde a la salida del primer perceptron de la capa, y[1] al segundo y asi*/
//	Col <double> d; /**d es el vector de salidas esperadas (solo se utiliza si hidden es false)*/
//	Col <double> error; /**error es el vector de error (d(n)-y(n)) por capa*/
	
public:
	Layer();
	~Layer();
	void calcular_salida();
	Col <double> out_layer();
	void corregir_pesos(); 
	void recibir_entradas(Col <double> a);
};

#endif



