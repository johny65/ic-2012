#include "rbf.h"

/**
 * @brief Constructor por defecto.
 */
RBF::RBF() : sigma2(0.5) {}


RBF::~RBF()
{
}


void RBF::set_centro(Punto &m)
{
	this->mu = m;
}


double RBF::clasificar(Punto &entrada)
{
	return gaussiana(entrada, this->mu, this->sigma2);
}
