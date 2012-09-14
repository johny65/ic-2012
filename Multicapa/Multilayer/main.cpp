#include<iostream>
//#include "armadillo"

#include "Network.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	vector<double> p;
	//p.push_back(4);
	p.push_back(2);
	//p.push_back(3);
	//p.push_back(2);
	p.push_back(1);
	Network A(p);
	//cout<<A.cant_capas()<<endl;
	A.entrenar("concent.csv");
	A.mostrar_pesos();
	//cout<<"Resultado de la clasificacion "<<s.back()<<endl;
	return 0;
}
