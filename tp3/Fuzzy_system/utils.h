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
 * Lee todas las entradas más la salida deseada. No agrega la entrada del sesgo.
 * Las salidas deseadas las mete en un vector aparte.
 *
 * @param archivo Nombre del archivo que se va a leer.
 * @param sd Vector donde se guardarán las salidas deseadas.
 * @return Matriz de datos leídos, cada fila corresponde a un patrón de entrada.
*/
vector< vector<double> > leer_csv(const char *archivo, vector<double> &sd);



struct trapezoide{
	double b,c; // b y c cortes que produce el grado de activacion del conjunto difuso
	double degree; //valor que toman los puntos b y c en el eje y.
};	
struct triangulo{
	double left;
	double center;
	double right;
	trapezoide A;
	void calcular_bc(double degree);
	void calcular_centro();
	bool pertenece(double);
	double calcular_degree(double &x); ///<recibe un punto se fija si pertenece al conjunto y calula el grado de membresia del mismo en caso de no pertenecer devuelve -1; 
};

/**
 * @brief Lee un archivo csv pero no separa las salidas deseadas.
 */
vector< vector<double> > leer_csv(const char *archivo);


/**
 * @brief Recibe una matriz de datos y genera un archivo que puede ser usado
 * por GNUplot para graficar esos datos.
 * @param v Matriz de datos a grabar.
 * @param name Es el nombre del archivo a generar.
 */
void crear_dat(vector<vector<double> > &v, const char *name);


/**
 * @brief Recibe un vector de datos y genera un archivo que puede ser usado
 * por GNUplot para graficar esos datos.
 * @param v Vector de datos a grabar.
 * @param name Es el nombre del archivo a generar.
 */
void crear_dat_vector(vector<double> &v, const char *name);


/**
 * @brief Guarda un archivo .csv con los datos pasados.
 * @param file Nombre del archivo para guardar.
 * @param datos Matriz con los datos.
 */
void guardar_csv(const char *file, vector< vector<double> > &datos);


/**
* @brief Recibe un vector de datos y genera un archivo con todos los pesos por 
* por perceptrón.
* @param pesos Vector de pesos a grabar.
*/
void pesos_a_archivo(vector< vector<double> > pesos); 


/**
* @brief Recibe el nombre de un archivo y crea un vector con los pesos de una red.
* @param v Vector de datos a grabar.
* @param archivo Es el nombre del archivo del que se van a extraer los datos.
*/
vector< vector<double> > pesos_desde_archivo(const char * archivo);


/**
* @brief Guarga los triangulos para graficarlos con GNUplot
*/
void crear_dat_conjuntos(vector<triangulo> &v, const char *name);

#endif
