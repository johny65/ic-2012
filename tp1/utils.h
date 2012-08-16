#ifndef utils_H
#define utils_H

#include <valarray>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector< valarray<double> > leer_csv(const char *archivo)
{
	vector< valarray<double> > todo;
	
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
		valarray<double> v(aux.get_allocator().allocate(aux.size()), aux.size());
		todo.push_back(v);
	}
	
	return todo;
}

#endif
