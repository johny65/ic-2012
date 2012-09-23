#ifndef RBF_H
#define RBF_H

#include "func.h"

/**
 * @brief Clase que representa una neurona con función de base radial (también
 * llamada unidad oculta).
 */
class RBF {
private:
	Punto mu; ///< Media (centro de la gaussiana)
	double sigma2; ///< Sigma cuadrado (varianza)

public:
	RBF();
	~RBF();
	void set_centro(Punto &m);
	double clasificar(Punto &entrada);
	
};

#endif