#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;

vector<double> init_weight(int nd)
{
	double w;
	vector<double> pesos;
	for(int i=0; i<nd; ++i){ //hasta nd xq el sesgo tambien tiene peso aletorio
		w=(rand()*1.0/RAND_MAX) - 0.5;
		//w = (rand()%1000) / 1000.0 - 0.5;
		pesos.push_back(w);
	}
	return pesos;
}

vector<double> sum(const vector<double> &y, const vector<double> &x)
{
	vector<double> r;
	int n=y.size();
	for(int i=0;i<n;++i){
		r.push_back(y[i]+x[i]);
	}
	return r;
}

vector<double> dif(const vector<double> &y, const vector<double> &x)
{
	assert(y.size() == x.size());
	vector<double> r;
	int n=y.size();
	for(int i=0;i<n;++i){
		r.push_back(y[i]-x[i]);
	}
	return r;
}

vector<double> prod_escalar(const vector<double> &x, double nu)
{
	vector<double> y;
	int n=x.size();
	for(int i=0;i<n;++i){
		y.push_back(nu*x[i]);
	}
	return y;
}

double dot(const vector<double> &x, const vector<double> &y)
{
	assert(y.size() == x.size());
	double p=0;
	//vector de pesos sin sesgo
	int n=x.size();
	for(int i=0; i<n; ++i){
		p+=x[i]*y[i];
	}
	return p;
}

vector<double> recalcular_pesos(const vector<double> &pv, double tasa,
	double s, double se, const vector<double> &datos){
		
	//np=pv+2*tasa*[se-s]*datos
	vector<double> np; //nuevos pesos
	np = sum(pv,prod_escalar(datos,tasa*(se-s)));
	return np;
}


double calc_error_x_epoca(double sal_d, double sal_o){
	/** @param sal_d salida deseada
	@param sal_o salida obtenida
	*/
	return abs(sal_d-sal_o);
}

double calc_error(vector<double> &x, vector<double> &y)
{
	double r = 0.0;
	for (size_t i=0; i<x.size(); ++i){
		r += (x[i] - y[i]) * (x[i] - y[i]);
	}
	return r / x.size();
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
	double res = (2.0/(1.0 + exp(-a*valor)))-1;
	return res;
}

double derivada_sigmoide(double x, double a = 1.0)
{
	double res = 2*(exp(-a*x)/(pow(1+exp(-a*x),2)));
	return res;
}

double energia(const vector<double> &s){
	double e=0;
	for(size_t i=0;i<s.size();i++) { 
		e+=s[i]*s[i];
	}
	return e;
}
