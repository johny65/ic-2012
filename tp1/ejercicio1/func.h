#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include <cmath>

using namespace std;

/**
	func.h maneja todas las funciones matemáticas utilizadas por la clase Perceptron
*/


vector<double> init_weight(int nd){
	/**
		@brief Rutina que inicializa el vector de pesos aletoriamente (valores
		entre [-0.5, 0.5]).
		@param nd es la longitud del vector a retornar.
		@return vector de pesos inicializados al azar
	*/
	double w;
	vector<double> pesos;
	srand(time(NULL));
	for(int i=0; i<nd+1; ++i){ //hasta nd+1 xq el sesgo tambien tiene peso aletorio
		w=(rand()*1.0/RAND_MAX) - 0.5;
		pesos.push_back(w);
	}
	return pesos;
}

vector<double> sum(vector<double> y,vector<double> x){
	/**
		@brief rutina que suma vectores componente a componente
	*/
	vector<double> r;
	int n=y.size()-1;
	for(int i=0;i<n;++i){
		r.push_back(y[i]+x[i]);
	}
	r.push_back(y.back());
	return r;
}

vector<double> dif(vector<double> y,vector<double> x){
	vector<double> r;
	int n=y.size()-1;
	for(int i=0;i<n;++i){
		r.push_back(y[i]-x[i]);
	}
	r.push_back(y.back());
	return r;
}

/**
 * Producto de un vector por un escalar (aunque el nombre no lo sugiera).
 */
vector<double> prod_escalar(vector<double> x, double nu){
	vector<double> y;
	int n=x.size();
	for(int i=0;i<n;++i){
		y.push_back(nu*x[i]);
	}
	return y;
}


double dot(vector<double> &x, vector<double> &y){
	if(x.size()!=y.size()){
		cerr<<"Vectores de diferente dimensión!"<<endl;
		return 0;
	}
	double p=0;
	//vector de pesos sin sesgo
	int n=x.size();
	for(int i=0; i<n; ++i){
		p+=x[i]*y[i];
	}
	return p;
}


vector<double> recalcular_pesos(vector<double> pv,double tasa,double s,double se,vector<double> datos){
	//np=pv+2*tasa*[se-s]*datos
	vector<double> np;
	np=sum(pv,prod_escalar(datos,2*tasa*(se-s)));
	return np;
}



/* Funciones de activación: */

/*
 * Tiene que aceptar parámetros (double, double) para que haya compatibilidad
 * con la sigmoide.
 */

double signo(double valor, double a = 1.0)
{
	if(valor>=0) return 1;
	else return -1;	
}

double sigmoide(double valor, double a = 1.0)
{
	double res = (1.0 - exp(-a*valor)) / (1.0 + exp(-a*valor));
	return res;
}


#endif
