#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Layer.h"

using namespace std;
/**
	@class Network se encarga de la comunicacion de las capas
*/

class Network {
private:
	//vector<Layer> R; /** R es el vector de capas, es decir la longitud del vector R determina la cantidad de capas en la red, siendo R[R.size()-1] la capa de salida*/
public:
	//Setear_arquitectura()  (idea funcion que setee las conexiones de las capas todos contra todos o como sea)
	Network();
	~Network();
};

#endif

