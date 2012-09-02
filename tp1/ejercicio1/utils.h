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
 * @file utils.h Maneja todas las rutinas de entrada/salida de archivos.
*/


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
vector< vector<double> > leer_csv(const char *archivo, vector<double> &sd);


/**
 * @brief Recibe una matriz de datos y genera un archivo que puede ser usado
 * por GNUplot para graficar esos datos.
 * @param v Matriz de datos a grabar.
 * @param name Es el nombre del archivo a generar.
 */
void crear_dat(vector<vector<double> > &v, const char *name);
void crear_dat_vector(vector<double>  &v, const char *name);


/**
 * @brief Rutina que genera un archivo txt que contiene las entradas de los
 * datos de prueba y la salida obtinada por el Perceptron.
 * @param entradas matriz de datos de entradas(sin resultado esperado)
 * @param salidas vector de salida calculado por el Perceptron
 * @param name nombre del archivo .txt a generar
*/
int generar_resultados(vector<vector<double> > &entradas,vector<double> &salidas,const char *name);

#endif
