#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <set>
#include "func.h"
#include "GNUplot.h"
#include "utils.h"

using namespace std;


double dist(Punto a, Punto b)
{
	assert(a.size() == b.size()); //puntos de la misma dimensión
	int D = a.size();
	
	double d = 0.0;
	for (int i=0; i<D; ++i){
		d += (a[i] - b[i])*(a[i] - b[i]);
	}

	return d; //no hace falta sacar raíz cuadrada
}

double dist(int x1, int y1, int x2, int y2)
{
	double d = pow((x1-x2), 2) + pow((y1-y2), 2);
	return d; //no saco raíz cuadrada
}

vector<double> init_weight(int nd)
{
	double w;
	vector<double> pesos;
	for(int i=0; i<nd; ++i){ //hasta nd xq el sesgo tambien tiene peso aletorio
		w=(rand()*1.0/RAND_MAX) - 0.5;
		pesos.push_back(w);
	}
	return pesos;
}

vector<double> sum(const vector<double> &y, const vector<double> &x)
{
	assert(y.size() == x.size());
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
	int n=x.size();
	for(int i=0; i<n; ++i){
		p+=x[i]*y[i];
	}
	return p;
}

double energia(const vector<double> &s){
	double e=0;
	for(size_t i=0;i<s.size();i++) { 
		e+=s[i]*s[i];
	}
	return e;
}

double signo(double valor)
{
	if(valor>=0) return 1;
	else return -1;	
}

double gaussiana(Punto &x, Punto &media, double sigma2)
{
	double res = exp(-dist(x, media) / (2*sigma2));
	return res;
}


double sigma(int n, double sigma_inicial, double tiempo){
	return sigma_inicial*exp(-1*n/tiempo);
}

double funcion_vecindad(int n,double &distancia, double sigma_inicial, double t){
	double s=sigma(n,sigma_inicial,t);
	if(distancia>=4*s) return 0;
	else return exp(-1*distancia/(2*pow(s,2)));
}

double eta_variable(int n, double eta_inicial, double t)
{
	return eta_inicial * exp(-n/t);
}