#ifndef utils_H
#define utils_H

#include <valarray>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;





vector< vector<double> > leer_csv(const char *archivo){
	vector< vector<double> > todo;
	
	vector<double> aux;
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		stringstream ss(linea);
		while(getline(ss, temp, ',')){
			stringstream ss2(temp);
			ss2>>val;
			aux.push_back(val);
		}
		todo.push_back(aux);
		aux.clear();
	

	}
	return todo;
}



	

#endif
