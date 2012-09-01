#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <iostream>
using namespace std;

vector<double> init_weight(int nd){
	/**
		@brief Rutina que inicializa el vector de pesos aletoriamente (valores
		entre [-0.5, 0.5]).
		@param nd es la longitud del vector a retornar (cantidad total de entradas teniendo en cuenta el -1)
		@return vector de pesos inicializados al azar
	*/
	double w;
	vector<double> pesos;
	srand(time(NULL));
	for(int i=0; i<nd; ++i){ //hasta nd xq el sesgo tambien tiene peso aletorio
		w=(rand()*1.0/RAND_MAX) - 0.5;
		pesos.push_back(w);
	}
	return pesos;
};

vector<double> sum(vector<double> y,vector<double> x){
	/**
		@brief rutina que suma vectores componente a componente
	*/
	vector<double> r;
	int n=y.size();
	for(int i=0;i<n;++i){
		r.push_back(y[i]+x[i]);
	}
	return r;
};

vector<double> dif(vector<double> y,vector<double> x){
	vector<double> r;
	int n=y.size();
	for(int i=0;i<n;++i){
		r.push_back(y[i]-x[i]);
	}
	return r;
};

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
};


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
};


/**
 * @param pv Pesos anteriores (viejos).
 * @param tasa
 * @param s Salida generada.
 * @param se Salida esperada.
 * @param datos Entradas.
 */
vector<double> recalcular_pesos(vector<double> pv, double tasa,
	double s,double se,vector<double> datos){
		
	//np=pv+2*tasa*[se-s]*datos
	vector<double> np; //nuevos pesos
	np = sum(pv,prod_escalar(datos,tasa*(se-s)));
	return np;
};


double calc_error(vector<double> &x, vector<double> &y)
{
	double r = 0.0;
	for (size_t i=0; i<x.size(); ++i){
		r += (x[i] - y[i]) * (x[i] - y[i]);
	}
	return r / x.size();
};


/* Funciones de activación: */

/*
 * Tiene que aceptar parámetros (double, double) para que haya compatibilidad
 * con la sigmoide.
 */

double signo(double valor, double a = 1.0)
{
	if(valor>=0) return 1;
	else return -1;	
};

double sigmoide(double valor, double a = 1.0)
{
	double res = (1.0 - exp(-a*valor)) / (1.0 + exp(-a*valor));
	return res;
}

