#include<iostream>
//#include "armadillo"

#include "Network.h"
using namespace std;

int main (int argc, char *argv[]) {
	
	vector<double> p;
	p.push_back(4);
	p.push_back(3);
	p.push_back(5);
	p.push_back(2);
	Network A(p);
	//cout<<A.cant_capas()<<endl;
	A.entrenar("tabla_OR.csv");
	
	return 0;
}
