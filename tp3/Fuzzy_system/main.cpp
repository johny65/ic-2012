#include <iostream>
#include <vector>
#include "Sistema.h"

using namespace std;

int main (int argc, char *argv[]) {
		
	//double b[6] = {-1.0, 1.0, 0.5, 2.5, 2, 4};
	//double b[6] = {-1.5, 1.5, 0, 3, 1.5, 4.5};
	double b[10] = {-0.5, 0.5, 0.25, 1.25, 0.75, 2.25, 1.75, 2.75, 2.5, 3.5};
	vector<double> I (b,b+sizeof(b)/sizeof(double));
	
	//double c[6] = {-72, 72, 36, 184, 148, 292};
	//double c[6] = {-110, 110, 0, 220, 110, 330};
	double c[10] = {-36.66, 36.66, 18.33, 91.65, 54.99, 164.99, 128.33, 201.65, 183.34, 256.66};
	vector<double> V (c,c+sizeof(c)/sizeof(double));

	double d[6] = {0, 20, 15, 35, 30, 50};
	//double d[6] = {-20, 20, 0, 40, 20, 60};
	vector<double> TE(d,d+sizeof(d)/sizeof(double));

	//double e[8] = {-1.6, 1.6, 0.8, 4.2, 3.4, 5.8, 5, 30};
	double e[8] = {-1.25, 1.25, 1.25, 3.5, 3.5, 6.5, 5, 30};
	vector<double> VAR(e,e+sizeof(e)/sizeof(double));
	
	Sistema Temp(I, V, TE, VAR);
	
	int o;
	while ((o = getopt(argc, argv, "hgs")) != -1){
		switch (o){
			case 'g':
				Temp.graficar_conjuntos();
				break;
			case 's':
				Temp.Simular_sincontrol();
				cin.get();
				return 0;
			case 'h':
				cout<<"\t-g Grafica conjuntos difusos.\n\t-s Simula sin control.\n\t-h Ayuda.\n";
				return 0;
		}
	}
	
	Temp.Simular_concontrol();
	cin.get();
	return 0;
}
