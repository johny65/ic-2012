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

/**
 * @brief Rutina para leer un archivo csv.
 *
 * Lee todas las entradas más la salida deseada. La entrada del sesgo la agrega
 * al principio. Las salidas deseadas las mete en un vector aparte.
 *
 * @param archivo Nombre del archivo que se va a leer.
 * @param sd Vector donde se guardarán las salidas deseadas.
 * @return Matriz de datos leídos, cada fila corresponde a un patrón de entrada.
*/
vector< vector<double> > leer_csv(const char *archivo, vector<double> &sd)
{
	vector< vector<double> > todo;
	
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


void crear_csv(vector<vector<double> > &v, const char *name){
	/**
		@brief Recibe una matriz de datos y genera un archivo con extension .csv (en general se usa para realizar pruebas sobre datos nunca vistos)
		@param v matriz de datos a grabar
		@param name es el nombre del archivo a generar
	*/

	std::ostringstream ss;
	ofstream out(name);
	vector<vector<double> >::iterator q=v.begin();
	while(q!=v.end()){
		int n=(*q).size();
		for(int i=1;i<n;i++){
			if(i!=n-1) ss << ((*q)[i]) << " ";
			else ss << ((*q)[i]) << endl;
		}
		q++;
		
	}
	out<<ss.str();
	out.close();
	
}

	

int generar_resultados(vector<vector<double> > &entradas,vector<double> &salidas,const char *name){
	/**
		@brief Rutina que genera un archivo txt que contiene las entradas de los datos de prueba y la salida obtinada por el Perceptron
		@param entradas matriz de datos de entradas(sin resultado esperado)
		@param salidas vector de salida calculado por el Perceptron
		@param name nombre del archivo .txt a generar
	*/

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
