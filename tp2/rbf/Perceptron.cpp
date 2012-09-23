#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include "Perceptron.h"
#include "utils.h"
#include "func.h"

using namespace std;

/**
 * @brief Constructor por defecto.
 */
Perceptron::Perceptron() {}


/**
 * @brief Destructor.
 */
Perceptron::~Perceptron() {}


/**
 * Inicializa los pesos del perceptrón en valores aleatorios.
 *
 * @param num_entradas Cantidad de pesos (cantidad de entradas que tiene el
 * perceptrón contando el sesgo)
 */
void Perceptron::inicializar_pesos(int num_entradas)
{
	this->pesos = init_weight(num_entradas);
}


/**
 * @brief Actualiza los pesos del perceptrón.
 *
 * Fórmula: wji(n+1) = wji(n) - eta*ej(n)*phii(n)
 *
 * @param ys Vector con las salidas de las neuronas de la capa anterior
 * conectadas a mí.
 * @param e Error en mi salida (e = y - d, donde y es mi salida y d es la
 * salida deseada).
 * @param eta Tasa de aprendizaje.
 */
void Perceptron::actualizar_pesos(vector<double> &ys, double e, double eta)
{
	assert(ys.size() == this->pesos.size());

	for (size_t i=0; i<this->pesos.size(); ++i){
		this->pesos[i] -= eta * e * ys[i];
	}
	
}


/**
 * @brief Función para mostrar por consola los pesos del perceptrón.
 */
void Perceptron::mostrar_pesos(){
	vector<double>::iterator q=this->pesos.begin();
	while(q!=pesos.end()){
		cout<<(*q)<<" , ";
		q++;
	}
	cout<<endl;
}


/**
 * @brief Devuelve la salida que calcula el perceptrón para una entrada dada
 * con los pesos actuales (salida lineal, es decir sólo es la combinación
 * lineal de sus entradas con sus pesos, sin pasar por una función de
 * activación).
 * 
 * @param D Vector con un patrón de entrada.
 * @return El valor de salida calculado.
 */
double Perceptron::clasificar(const vector<double> &D)
{
	return dot(D, this->pesos);
}
