#include<iostream>

#include "Network.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	vector<double> p;
	//p.push_back(4);
	p.push_back(2);
	//p.push_back(10);
	//p.push_back(10);
	p.push_back(1);
	Network A(p);
	//cout<<A.cant_capas()<<endl;
	//A.entrenar("tabla_XOR.csv");
	A.entrenar("xorvar.csv");
	//A.entrenar("test.csv");
	//A.entrenar("concent.csv");
	//A.mostrar_pesos();
	//pruebo con un dato 
	vector<double> x,s;
	x.push_back(1); 	x.push_back(1);
	s=A.clasificar(x);
	cout<<"Resultado "<<endl;
	for(int i=0;i<s.size();i++) { cout<<s[i]<<endl; }
	return 0;
}
