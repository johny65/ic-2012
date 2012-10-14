#include <iostream>
#include <vector>
#include "Sistema.h"

using namespace std;


int main (int argc, char *argv[]) {

	//double a[20]={0.0, 7.2, 3.6, 10.8, 7.2, 14.4, 10.8, 18.0,14.4,21.6,18.0,25.2,21.6,28.8,25.2,32.4,28.8,36.0,32.4,39.6};
	double a[10] = {-10, 10, 0, 20, 10, 30, 20, 40, 30, 50};
	vector<double> T (a,a+sizeof(a)/sizeof(double));

	double b[6] = {-1.5, 1.5, 0.75, 2.25, 1.5, 4.5};
	vector<double> I (b,b+sizeof(b)/sizeof(double));
	
	double c[6] = {-110, 110, 55, 165, 110, 330};
	vector<double> V (c,c+sizeof(c)/sizeof(double));

	double d[6] = {-5, 25, 15, 35, 25, 55};
	vector<double> TE(d,d+sizeof(d)/sizeof(double));

	//double e[10] = {-5, 5, 0, 10, 5, 15, 10, 20, 15, 25};
	double e[8] = {-2.5, 2.5, 1.25, 3.75, 2.5, 7.5, 5, 30};
	vector<double> VAR(e,e+sizeof(e)/sizeof(double));

	
	Sistema Temp(T,I,V);
	Temp.set_conjuntos(TE, VAR);
	//Temp.Simular_sincontrol();
	Temp.Simular_concontrol();
	
	cin.get();
	
	return 0;
}
