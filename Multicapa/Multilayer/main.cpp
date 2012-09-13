#include<iostream>
//#include "armadillo"

#include "Network.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	vector<double> p;
	p.push_back(2);
	p.push_back(1);
//	p.push_back(1);
//	p.push_back(2);
	Network A(p);
	//cout<<A.cant_capas()<<endl;
	A.entrenar("tabla_XOR.csv");
	
	return 0;
}
