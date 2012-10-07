#include "Sistema.h"

Sistema::Sistema(int cant_conj,vector<double> intervalos) { 
	/**
	@param cant_conj: cantidad de conjuntos difusos.
	@param intervalos de los conjuntos difusos (el tamanio del vector debe ser 2*cant conjuntos contiene los valores left y right de los triangulos)
	*/
	triangulo aux;
	for(int i=0;i<cant_conj;i+=2) { 
		aux.left=intervalos[i];
		aux.right=intervalos[i+1];
		this->conjuntos.push_back(aux);
	}
}

Sistema::~Sistema() {
	
}

