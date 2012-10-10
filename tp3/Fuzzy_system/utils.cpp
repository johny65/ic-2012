#include <valarray>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include "utils.h"

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
		//aux.push_back(-1); //para las redes RBF no hay que poner el -1 en la entrada
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


void triangulo::calcular_centro(){
	double r=(this->right-this->left)/2;
	this->center=this->left+r;
}

bool triangulo::pertenece(double x){
	if(x<this->right && x>this->left)
		return true;
	else return false;
}

void triangulo::calcular_bc(double degree){
	double m1=1/(this->center-this->left);
	double m2=1/(this->center-this->right);
	this->A.a=this->left;
	this->A.b=(degree+this->left*m1)/m1;
	this->A.c=(degree+this->right*m2)/m2;
	this->A.d=this->right;
	this->A.degree=degree;
	
}

double triangulo::calcular_degree(double &x){
		double m;//pendiente
		if(x>this->center){
			m=1/(this->center-this->left);
			return m*(x-this->left);
		}
		else{
			m=1/(this->center-this->right);
			return m*(x-this->right);			
		}

}


vector< vector<double> > leer_csv(const char *archivo)
{
	vector< vector<double> > todo;
	
	vector<double> aux;
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		//aux.push_back(-1);
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

void crear_dat(vector<vector<double> > &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<vector<double> >::iterator q=v.begin();
	while(q!=v.end()){
		int n=(*q).size();
		for(int i=0;i<n;++i){
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
		ss << (*q) << "\n";
		q++;
	}
	out<<ss.str();
	out.close();

}

void guardar_csv(const char *file, vector< vector<double> > &datos)
{
	ofstream out(file, ios::trunc);
	for (size_t i=0; i<datos.size(); ++i){
		for (size_t j=0; j<datos[i].size()-1; ++j){
			out<<datos[i][j]<<", ";
		}
		out<<datos[i].back()<<endl;
	}
	out.close();
}

void pesos_a_archivo(vector< vector<double> > pesos){
	ofstream out("pesos.txt", ios::app);
	std::ostringstream aux;
	for (size_t i=0; i<pesos.size(); i++){
		for (size_t j=0; j< pesos[i].size(); j++){
				aux<<pesos[i][j]<<" ";
		}
		aux<<endl;
	}
	aux<<endl;
	out<<aux.str();
	out.close();
}

// Cargar los pesos de un Archivo a una red

vector< vector<double> > pesos_desde_archivo(const char * archivo){
	vector< vector<double> > pesos;
	vector<double> aux;
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		stringstream ss(linea);
		while(getline(ss, temp, ' ')){
			stringstream ss2(temp);
			ss2>>val;
			aux.push_back(val);
		}
		pesos.push_back(aux);
		aux.clear();
	}
	return pesos;
}


void crear_dat_conjuntos(vector<triangulo> &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<triangulo>::iterator q=v.begin();
	while(q!=v.end()){
		ss << (*q).left << " " << 0.0<< "\n";
		ss << (*q).center << " " << 1.0 << "\n";
		ss << (*q).right << " " << 0.0 << "\n";
		q++;
	}
	out<<ss.str();
	out.close();
}


double calcular_centroide(trapezoide A,trapezoide B){
	double centro_A=A.b+(A.c-A.b)/2;
	double centro_B=B.b+(B.c-B.b)/2;
	double c=(A.degree*(A.c-A.a)*centro_A+B.degree*(B.c-B.a)*centro_B)/(A.degree*(A.c-A.a)+B.degree*(B.c-B.a));
	return c;
}