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
	Swarm S(20,4,0.12,0.15,rango, 25);
	S.Volar(100,1);
	return 0;
}

