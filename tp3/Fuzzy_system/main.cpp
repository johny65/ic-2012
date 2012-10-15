#include <iostream>
#include <vector>
#include "Sistema.h"

using namespace std;

int main (int argc, char *argv[]) {
		
	double b[6] = {-1.0, 1.0, 0.5, 2.5, 2, 4};
	vector<double> I (b,b+sizeof(b)/sizeof(double));
	
	double c[6] = {-72, 72, 36, 184, 148, 292};
	vector<double> V (c,c+sizeof(c)/sizeof(double));

	double d[6] = {0, 20, 15, 35, 30, 50};
	vector<double> TE(d,d+sizeof(d)/sizeof(double));

	double e[8] = {-2.5, 2.5, 1.25, 3.75, 2.5, 7.5, 5, 30};
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
