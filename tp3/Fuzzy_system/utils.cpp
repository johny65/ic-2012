#include "utils.h"
void triangulo::calcular_centro(){
	this->center=(this->right-this->left)/2;
}

bool triangulo::pertenece(double x){
	if(x<this->right && x>this->left)
		return true;
	else return false;
}
