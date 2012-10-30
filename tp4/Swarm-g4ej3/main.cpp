#include<iostream>
#include <vector>
#include "Swarm.h"
using namespace std;

int main (int argc, char *argv[]) {
	vector<pair<double,double> > rango;
	pair<double,double> a;
	a.first=-512;
	a.second=512;
	rango.push_back(a);
	Swarm S(10,1,0.2,0.15,false,rango, 7);
	S.Volar(1000,5);
	return 0;
}

