#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <boost/numeric/mtl/mtl.hpp>
#include "utils.h"
#include "Layer.h"

using namespace std;
using namespace mtl;
/**
	@class Network se encarga de la comunicacion de las capas
*/

class Network {
private:
	std::vector<Layer> R; /** R es el vector de capas, es decir la longitud del vector R determina la cantidad de capas en la red, siendo R[R.size()-1] la capa de salida*/
	dense2D<double> Datos;
	dense_vector<double> d;///< salida esperada para cada fila de la matrix Datos;
public:
	//Setear_arquitectura()  (idea funcion que setee las conexiones de las capas todos contra todos o como sea)
	Network();
	~Network();
	
	void entrenar(const char *name);
	void val_cross(const char *ruta);
	void probar(const char *name);
	dense_vector<double> clasificar(); //el dense_vector de salida contiene 1 solo elemento en caso que en la capa de salida solo exista una sola neurona
	
};

#endif

