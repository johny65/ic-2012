#ifndef utils_H
#define utils_H

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
	utils.h maneja todas las rutinas de entrada/salida de archivos
*/


vector< vector<double> > leer_csv(const char *archivo, vector<double> &sd);
void crear_csv(vector<vector<double> > &v, const char *name);
int generar_resultados(vector<vector<double> > &entradas,vector<double> &salidas,const char *name);


#endif
