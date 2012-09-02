#include <valarray>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include "GNUplot.h"

using namespace std;

vector< vector<double> > leer_csv(const char *archivo, vector<double> &sd)
{
	vector< vector<double> > todo;
	sd.clear();
	
	vector<double> aux;
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		aux.push_back(-1);
		stringstream ss(linea);
		while(getline(ss, temp, ',')){
			stringstream ss2(temp);
			ss2>>val;
			aux.push_back(val);
		}
		//pasar la salida deseada al vector de salidas deseadas:
		sd.push_back(aux.back());
		aux.erase(aux.end()-1);
		
		todo.push_back(aux);
		aux.clear();
	}
	return todo;
}

void crear_dat(vector<vector<double> > &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<vector<double> >::iterator q=v.begin();
	while(q!=v.end()){
		int n=(*q).size();
		for(int i=1;i<n;++i){
			if(i!=n-1) ss << ((*q)[i]) << " ";
			else ss << ((*q)[i]) << endl;
		}
		q++;
	}
	out<<"# archivo temporal usado para graficar los puntos de entrada en gnuplot\n";
	out<<ss.str();
	out.close();
	
}

void crear_dat_vector(vector<double> &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<double>::iterator q=v.begin();
	while(q!=v.end()){
			ss << (*q) << "\n ";
			
		q++;
	}
	out<<"# archivo temporal usado para graficar los puntos de entrada en gnuplot\n";
	out<<ss.str();
	out.close();
	
}

int generar_resultados(vector<vector<double> > &entradas,vector<double> &salidas,const char *name){
	
	std::ostringstream ss;
	ofstream out(name);
	vector<vector<double> >::iterator q=entradas.begin();
	int c=0;
	while(q!=entradas.end()){
		int n=(*q).size();
		for(int i=0;i<n;i++){
			ss << ((*q)[i]) << ", ";
		}
		ss << salidas[c] << endl;
		c++;
		q++;
		
	}
	out<<ss.str();
	out.close();
	return 1;
}
