#ifndef FUNC_H
#define FUNC_H

/**
	@file func.h Maneja todas las funciones matemáticas.
*/

#include <vector>
#include <cmath>
#include <ctime>

using namespace std;
typedef vector<double> Punto;


/**
 * @brief Calcula la distancia euclídea entre 2 puntos de cualquier dimensión
 * (sin calcular la raíz cuadrada).
 */
double dist(Punto a, Punto b);


/**
 * @brief Calcula la distancia euclídea entre 2 puntos de una grilla bidimensional
 * (sin calcular la raíz cuadrada).
 * Los puntos son (x1,y1) y (x2,y2).
 */
double dist(int x1, int y1, int x2, int y2);


/**
 * @brief Algoritmo de k-means.
 * @param datos Vector con los puntos de datos de entrada.
 * @param k Cantidad de clústers.
 * @return Un vector con los k centroides (medias) calculados.
 */ 
vector<Punto> k_means(vector<Punto> datos, int k);


/**
 * @brief Rutina que inicializa el vector de pesos aletoriamente (valores
 * entre [-0.5, 0.5]).
 * @param nd Es la longitud del vector a retornar (cantidad total de entradas
 * teniendo en cuenta el -1).
 * @return Vector de pesos inicializados al azar.
 */
vector<double> init_weight(int nd);


/**
 * @brief Rutina que suma vectores componente a componente.
 */
vector<double> sum(const vector<double> &y, const vector<double> &x);


/**
 * @brief Rutina que resta vectores componente a componente.
 */
vector<double> dif(const vector<double> &y, const vector<double> &x);


/**
 * @brief Producto de un vector por un escalar (aunque el nombre no lo sugiera).
 */
vector<double> prod_escalar(const vector<double> &x, double nu);


/**
 * @brief Producto punto entre 2 vectores.
 */
double dot(const vector<double> &x, const vector<double> &y);


/**
 * @brief Calcula la energía de un vector (suma de los cuadrados).
 * @param s Vector.
 */
double energia(const vector<double> &s);


/**
 * @brief Función signo.
 */
double signo(double valor);


/**
 * @brief Función de base radial gaussiana.
 * @param x Punto a evaluar.
 * @param media Media para la gaussiana (mu).
 * @param sigma2 Varianza para la gaussiana (sigma cuadrado).
 */
double gaussiana(Punto &x, Punto &media, double sigma2);

/**
@brief Funcion sigma variante con el tiempo
@param n iteracion en la que estoy parado
@param sigma_inicial valor inicial de desvio
@param tiempo es una constante de tiempo (probar t igual al numero total de iteraciones)
*/
double sigma(int n, double sigma_inicial, double tiempo);


/**
@brief Funcion de vecindad para saber que nodos debo afectar cuando una neurona dada gana utiliza la funcion sigma
@param n iteracion que estoy corriendo a la hora del calculo
@param distancia es la distancia entre la neurona ganadora y la que se va a actualizar
@param sigma_inicial es el desvio inicial elegido
@param t es una constante de tiempo
*/
double funcion_vecindad(int n,double &distancia, double sigma_inicial, double t);


/**
 * @brief Función para actualizar la tasa de aprendizaje a lo largo del tiempo.
 * @param n Instante de tiempo actual.
 * @param eta_inicial Valor inicial.
 * @param t Constante de tiempo.
 */
double eta_variable(int n, double eta_inicial, double t);

#endif
