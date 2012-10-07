#include "utils.h"
void triangulo::calcular_centro(){
	this->center=(this->right-this->left)/2;
}

bool triangulo::pertenece(double x){
	if(x<this->right && x>this->left)
		return true;
	else return false;
}

void triangulo::calcular_bc(double degree){
	double m1=1/(this->center-this->left);
	double m2=1/(this->center-this->right);
	this->A.b=(degree+this->left*m1)/m1;
	this->A.c=(degree+this->right*m2)/m2;

}
