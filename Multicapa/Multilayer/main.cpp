#include<iostream>
//#include "armadillo"

#include "Network.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	vector<double> p;
	//p.push_back(4);
	p.push_back(2);
	p.push_back(3);
	p.push_back(2);
	p.push_back(1);
	Network A(p);
	//cout<<A.cant_capas()<<endl;
	A.entrenar("concent.csv");
	vector<double> e,s;
	e.push_back(0.5);//0.201659414);
	e.push_back(0.5);//0.712270393);
	s=A.clasificar(e);
	cout<<"Resultado de la clasificacion "<<s.back()<<endl;
	return 0;
}
