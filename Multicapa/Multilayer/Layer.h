#ifndef LAYER_H
#define LAYER_H

#include <boost/numeric/mtl/mtl.hpp>
 
using namespace mtl;

class Layer {
private:
	int id; /** identifica la capa (capa numero 1,2, etc)*/
	int NP; /**NP numero de perceptrones por capa (este numero sera igual al numero de filas de la matriz M)*/
	
	bool hidden; /**hidden=True la capa es oculta, caso contrario es la capa de salida*/
	
	dense2D<double> M; /**M matriz correspondiente a la capa id en cada fila i tiene los pesos correspondiente al i-esimo perceptron contenido en ella*/
	dense_vector<double> x; /**x es el vector de entradas con sesgo incluido*/	
	dense_vector<double> y; /**y es el vector de salidas para la capa en cuestion, el emento y[0] corresponde a la salida del primer perceptron de la capa, y[1] al segundo y asi*/
	dense_vector<double> d; /**d es el vector de salidas esperadas (solo se utiliza si hidden es false)*/
	dense_vector<double> error; /**error es el vector de error (d(n)-y(n)) por capa*/
	
public:
	Layer();
	~Layer();
};

#endif

