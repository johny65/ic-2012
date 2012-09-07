#include "Layer.h"

Layer::Layer(): id(1),NP(1),hidden(false) {
	
}

Layer::~Layer() {
	
}
dense_vector<double> Layer::out_layer ( ) {
	return this->y;
}

void Layer::corregir_pesos ( ) {
	
}

void Layer::calcular_salida(){
	this->y=this->M*this->x;
}

void Layer::recibir_entradas(dense_vector<double> a){
	this->x=a;
}
