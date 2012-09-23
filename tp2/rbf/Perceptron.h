#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>

using namespace std;


/**
 * @brief Clase Perceptron Simple
 */
class Perceptron {
private:
	vector<double> pesos; ///< Vector de pesos
	
public:
	Perceptron();
	~Perceptron();	
	void inicializar_pesos(int);
	double clasificar(const vector<double> &D);
	void actualizar_pesos(vector<double> &ys, double e, double eta);
	void mostrar_pesos();

};

#endif
