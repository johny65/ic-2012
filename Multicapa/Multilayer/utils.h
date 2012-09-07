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
#include <boost/numeric/mtl/mtl.hpp>

using namespace std;
using namespace mtl;

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
dense2D<double> leer_csv(const char *archivo, dense_vector<double> &sd);




#endif
