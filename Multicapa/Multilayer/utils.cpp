#include <valarray>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <boost/numeric/mtl/mtl.hpp>



using namespace std;
using namespace mtl;

dense2D<double> leer_csv(const char *archivo, dense_vector<double> &sd)
{
	dense2D<double> todo(50,50);
	//sd.clear();
	
	//std::vector<double> aux;
	int r=0,c=0; //r: rows c: column
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		todo(r,c)=-1; c++;
		stringstream ss(linea);
		while(getline(ss, temp, ',')){
			stringstream ss2(temp);
			ss2>>val;
			todo(r,c)=val;
			c++;
		}
		sd[r]=todo(r,c);
		r++;
	}
	
	return todo;
}


