#include "Network.h"

Network::Network() {
	
}

Network::~Network() {
	
}

void Network::entrenar (const char * name) {
	/** 
		@brief entrena la red neuronal
		@param name nombre del archivo que contiene los datos
	*/
	///< 1- Abro el archivo de datos;
	this->Datos=leer_csv(name,d);
	cout<<Datos;
	
}

void Network::val_cross (const char * ruta) {
	
}

void Network::probar (const char * name) {
	
}

dense_vector<double> Network::clasificar ( ) {
	
}

