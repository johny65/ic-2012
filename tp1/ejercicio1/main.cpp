#include<iostream>
#include <valarray>
#include <vector>

#include "Perceptron.h"
#include "utils.h"
#include <iterator>




using namespace std;

int main (int argc, char *argv[]) {
	vector<vector<double> > bd;
	bd=leer_csv("datos.csv");
	Perceptron C(0.005);
	C.entrenar(bd);
	vector<double> s; s.push_back(-0.95); s.push_back(0.8);
	C.clasificar(s);
	C.result();

	return 0;
}

