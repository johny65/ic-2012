#include<iostream>
#include "Network.h"

using namespace std;

int main (int argc, char *argv[]) {
	
	vector<double> p;
	p.push_back(3);
	p.push_back(2);
	p.push_back(2);
	Network A(3, p);
	
	A.entrenar("tabla_OR.csv");
	
	return 0;
}
