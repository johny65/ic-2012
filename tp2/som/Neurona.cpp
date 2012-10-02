#include <algorithm>
#include "Neurona.h"
#include "func.h"
#include <limits>
#include <iostream>
#include <cmath>

/**
 * @brief Constructor.
 */
Neurona::Neurona() {}


/**
 * @brief Destructor.
 */
Neurona::~Neurona() {}


/**
 * @brief Inicializa aleatoriamente los pesos de la neurona.
 * @param n Cantidad de pesos que va a tener.
 */
void Neurona::inicializar_pesos(int n)
{
	this->pesos = init_weight(n);
}


/**
 * @brief Calcula el producto punto entre un patrón de entrada y mis pesos.
 * @param x Patrón de entrada.
 */
double Neurona::evaluar(vector<double> &x)
{
	return dist(x, this->pesos);
}


/**
 * @brief Actualiza los pesos de la neurona.
 *
 * La fórmula para actualizar los pesos de la neurona j es la siguiente
 * (Haykin, pág. 451):
 * 
 *     wj(n+1) = wj(n) + eta(n) * hji(n) * (x - wj(n))
 *
 * donde:
 *     eta(n) es la tasa de aprendizaje que depende del tiempo
 *     hji(n) es el valor de la función de vecindad para la neurona j con
 * respecto a la neurona ganadora i del patrón de entrada x, y depende del
 * instante de tiempo n
 *     x es el patrón de entrada. 
 *
 * @param x Patrón de entrada.
 * @param eta Tasa de aprendizaje.
 * @param h Valor para la neurona de la función de vecindad.
 */
void Neurona::actualizar_pesos(vector<double> &x, double eta, double h)
{
	double resta;
	for (size_t i=0; i<this->pesos.size(); ++i){
		resta = x[i] - this->pesos[i];
		if(isnan(resta)) resta=0;
		//if(isnan(h)) h=0; //if (resta < numeric_limits<double>::min()) resta = 0.0;
		this->pesos[i] += eta * h * (resta);
		
	}
}


/**
 * @brief Inicializa el vector de activaciones para ir sumando la cantidad de
 * veces que se activa para una clase determinada.
 * @param n Cantidad de clases.
 */
void Neurona::init_activaciones(int n)
{
	this->activaciones = vector<int>(n, -1);
}


/**
 * @brief Contar una activación para la clase k.
 */
void Neurona::sumar_clase(int k)
{
	this->activaciones[k]++;
}


void Neurona::set_clase()
{
	vector<int>::iterator m = max_element(this->activaciones.begin(),
		this->activaciones.end());
	if (*m == -1)
		this->clase = -1;
	else
		this->clase = distance(this->activaciones.begin(), m);
}
