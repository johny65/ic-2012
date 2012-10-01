#ifndef _NEURONA_H_
#define _NEURONA_H_

#include <vector>

using namespace std;

class Neurona {
private:
	vector<double> pesos; ///< Vector de pesos

	//Para clasificación:
	
	int clase; ///< Clase de la neurona
	vector<int> activaciones; ///< Cantidad de activaciones por clase
	
public:
	Neurona();
	~Neurona();
	void inicializar_pesos(int);
	double evaluar(vector<double> &x);
	void actualizar_pesos(vector<double> &x, double eta, double h);
	vector<double>& get_pesos() { return this->pesos; }

	void init_activaciones(int n);
	void sumar_clase(int k);
	void set_clase();
	int get_clase(){ return this->clase; }
};

#endif
