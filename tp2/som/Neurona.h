#ifndef _NEURONA_H_
#define _NEURONA_H_

#include <vector>

using namespace std;

class Neurona {
private:
	vector<double> pesos; ///< Vector de pesos
	
public:
	Neurona();
	~Neurona();
	void inicializar_pesos(int);
	double evaluar(vector<double> &x);
	
};

#endif