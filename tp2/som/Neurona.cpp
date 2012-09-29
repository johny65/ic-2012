#include "Neurona.h"
#include "func.h"

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
	return dot(x, this->pesos);
}
