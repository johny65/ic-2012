#include "Neurona.h"
#include "func.h"

/**
 * @brief Constructor.
 */
Neurona::Neurona() { this->cant_activaciones=0;}


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
	//vector<double> d=dif(x, this->pesos);
	return dot(x,this->pesos);
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
	for (size_t i=0; i<this->pesos.size(); ++i){
		this->pesos[i] += eta * h * (x[i] - this->pesos[i]);
	}
	this->cant_activaciones++;
}

void Neurona::set_position(pair<int,int> P){
	this->Pos=P;
}
pair<int, int> Neurona::position(){
	return this->Pos;
}

peso_act Neurona::devolver_peso_act(){
	peso_act N;
	
	N.weight=this->pesos;
	N.cant_act=this->cant_activaciones;
	return N;
	
}

bool Neurona::es_vecino(pair<int, int> N){
	if(abs(N.first-this->Pos.first)==1 || abs(N.second-this->Pos.second)==1)
		return true;
	else 
		return false;
	
}
