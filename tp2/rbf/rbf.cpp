#include "rbf.h"

/**
 * @brief Constructor por defecto.
 */
RBF::RBF() : sigma2(0.5) {}


/**
 * @brief Destructor.
 */
RBF::~RBF() {}


/**
 * @brief Setea el centro de la función de base radial.
 * @param m Centro.
 */
void RBF::set_centro(Punto &m)
{
	this->mu = m;
}


/**
 * @brief Evalúa una entrada a través de la función de base radial.
 * @param entrada Dato de entrada.
 */
double RBF::clasificar(Punto &entrada)
{
	return gaussiana(entrada, this->mu, this->sigma2);
}
