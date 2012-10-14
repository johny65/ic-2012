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


/**
 * @brief Calcula el punto centro del triángulo (en el eje x).
 */
void triangulo::calcular_centro(){
	double r=(this->right-this->left)/2;
	this->center=this->left+r;
}


/**
 * @brief Devuelve si un punto `x` está dentro del triángulo (en el eje x).
 */
bool triangulo::pertenece(double x){
	if(x<this->right && x>this->left)
		return true;
	else return false;
}


/**
 * @brief Trunca el triángulo a una altura `degree` (queda un trapecio).
 */
void triangulo::calcular_bc(double degree){
	double m1=1/(this->center-this->left);
	double m2=1/(this->center-this->right);
	this->A.a=this->left;
	this->A.b=(degree+this->left*m1)/m1;
	this->A.c=(degree+this->right*m2)/m2;
	this->A.d=this->right;
	this->A.degree=degree;
}

/**
 * @brief Calcula el grado de activación de un punto `x`.
 */
double triangulo::calcular_degree(double &x){
	if (!pertenece(x))
		return 0.0;
	double m;//pendiente
	if(x>this->center){
		m=(this->right-this->center);
		return (1+(this->center-x)/m);
	}
	else{
		m=(this->center-this->left);
		return ((x-this->left)/m);			
	}

}

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


void crear_dat_conjuntos(vector<triangulo> &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<triangulo>::iterator q=v.begin();
	
	
	//guardo los triangulos interiores completos
	while(q!=v.end()){
		if(q+1==v.end()){
			ss << (*q).left << " " << 0.0<< "\n";
			ss << (*q).center << " " << 1.0 << "\n";
		}
		else{
			ss << (*q).left << " " << 0.0<< "\n";
			ss << (*q).center << " " << 1.0 << "\n";
			ss << (*q).right << " " << 0.0 << "\n";
		}
		q++;
	}

	
	out<<ss.str();
	out.close();
}


double calcular_centroide(trapezoide A,trapezoide B){
	double centro_A=A.b+(A.c-A.b)/2;
	double centro_B=B.b+(B.c-B.b)/2;
	double c=(A.degree*(A.c-A.a)*centro_A+B.degree*(B.c-B.a)*centro_B)/(A.degree*(A.c-A.a)+B.degree*(B.c-B.a));

	double cA = (A.d - A.a)+A.a;
	double cB = (B.d - B.a)+B.a;
	double r = cA * A.degree + cB * B.degree;
	r /= (A.degree + B.degree);

	cout<<"C andrés: "<<c<<" R mío: "<<r<<endl;
	return r;
}

double calcular_centroide_unico(triangulo A){
	return ((A.left+A.center+A.right)/3);
}
