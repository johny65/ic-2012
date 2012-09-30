#ifndef _NEURONA_H_
#define _NEURONA_H_

#include <vector>

using namespace std;

struct peso_act{
	vector<double> weight;
	int cant_act;
};

class Neurona {
private:
	vector<double> pesos; ///< Vector de pesos
	pair<int,int> Pos;
	int cant_activaciones;
	
public:
	Neurona();
	~Neurona();
	void inicializar_pesos(int);
	double evaluar(vector<double> &x);
	void actualizar_pesos(vector<double> &x, double eta, double h);
	vector<double> get_pesos() { return this->pesos; }
	void set_position(pair<int,int> );
	pair<int, int> position();
	peso_act devolver_peso_act(); //Devuelve los valores de los pesos y la cantidad de veces que se activo la neurona
	bool es_vecino(pair<int, int>);
};

#endif
