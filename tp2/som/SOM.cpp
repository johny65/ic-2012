#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "SOM.h"
#include "utils.h"
#include "func.h"


/**
 * @brief Constructor.
 */
SOM::SOM() : eta(0.01)
{
	srand(time(NULL) + getpid());
}


/**
 * @brief Destructor.
 */
SOM::~SOM() {}


/**
 * @brief Fija la tasa de aprendizaje de la red.
 * @param n Tasa de aprendizaje nueva.
 */
void SOM::set_tasa(double n)
{
	this->eta = n;
}


/**
 * @brief Fija el valor de sigma inicial.
 * El mismo es usado para calcular el valor de sigma variable con el tiempo
 * para la función de vecindad.
 */
void SOM::set_sigma(double s)
{
	this->sigma = s;
}


/**
 * @brief Fija el valor t usado para calcular el valor de sigma variable con
 * el tiempo para la función de vecindad.
 */
void SOM::set_t(double t)
{
	this->t = t;
}


/**
 * @brief Comprueba que se haya seteado una arquitectura y aborta la ejecución
 * en caso contrario.
 */
void SOM::verificar_inicializada()
{
	if (this->grilla.empty()){
		cout<<"No se configuró ninguna arquitectura para la red.\n";
		exit(-1);
	}
}


/**
 * @brief Inicializa el mapa con una matriz de neuronas de tamaño MxN.
 */
void SOM::inicializar(int M, int N)
{
	this->grilla = Matriz(M, vector<Neurona>(N));
	this->M = M;
	this->N = N;

	/* valores por defecto: si no se establecen valores específicos después,
	 * estos parámetros toman los valores recomendados por Haykin (pág. 453)
	 * para un grilla 2D:
	 * sigma: igual al "radio" de la grilla
	 * t: 1000/log(sigma)
	 */
	this->sigma = min(M, N)/2.0;
	this->t = 1000/log(this->sigma);
}


/**
 * @brief Inicializa todos los pesos de todas las neuronas de la red.
 */
void SOM::inicializar_pesos()
{
	for (int i=0; i<this->M; ++i){
		for (int j=0; j<this->N; ++j){
			this->grilla[i][j].inicializar_pesos(this->datos[0].size());
		}
	}
}


/**
 * @brief Busca la neurona ganadora para un patrón de entrada.
 * @param x Patrón de entrada.
 * @param i Por acá devuelve la fila de la neurona ganadora.
 * @param j Por acá devuelve la columna de la neurona ganadora.
 */
void SOM::competir(vector<double> &x, int &i, int &j)
{
	double win = 0.0;
	int wini = -1, winj = -1;
	double aux;

	//recorro todas las neuronas y veo cuál da mayor producto interno con la entrada
	for (int f=0; f<this->M; ++f){
		for (int c=0; c<this->N; ++c){
			aux = this->grilla[f][c].evaluar(x);
			if (aux > win){
				win = aux;
				wini = f;
				winj = c;
			}
		}
	}
	//resultados
	i = wini; j = winj;
	
}


/**
 * @brief Actualiza los pesos de todas las neuronas según las reglas del SOM.
 *
 * A partir de la neurona ganadora para un patrón de entrada, se actualizan los
 * pesos usando una función de vecindad que depende de la distancia de la ganadora
 * hacia las demás.
 * 
 * @param iganadora Fila de la neurona ganadora.
 * @param jganadora Columna de la neurona ganadora.
 * @param x Patrón de entrada actual.
 * @param n Instante actual de tiempo discreto.
 */
void SOM::actualizar_pesos(int iganadora, int jganadora, vector<double> &x, int n)
{
	//cout<<"Neurona ganadora: "<<iganadora<<" "<<jganadora<<endl;
	double r, h;
	for (int i=0; i<this->M; ++i){
		for (int j=0; j<this->N; ++j){
			r = dist(iganadora, jganadora, i, j);
			h = funcion_vecindad(n, r, this->sigma, this->t);
			//cout<<setw(9)<<h<<" | ";

			this->grilla[i][j].actualizar_pesos(x, this->eta, h);
		}
		//cout<<endl;
	}
}

	
		

/**
 * @brief Entrena la red neuronal.
 * @param name Nombre del archivo que contiene los datos.
 */
void SOM::entrenar(const char *name)
{
	verificar_inicializada();
	
	//Abro el archivo de datos:
	vector<double> salidas_escalares;
	this->datos = leer_csv(name, salidas_escalares);

	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo."<<endl; return;}

	//inicializo los pesos de la red
	inicializar_pesos();

	//vector con índices para aleatorizar entradas
	int cant_patrones_entrada = datos.size();
	vector<int> indices(cant_patrones_entrada);
	for (size_t i=0; i<indices.size(); ++i){
		indices[i] = i;
	}
	random_shuffle(indices.begin(), indices.end());

	//empiezo el entrenamiento
	int it = 0; //iteraciones
	while (it < 5000){ ///<\todo detener cuando nos se observen cambios
		
		for (int i=0; i<cant_patrones_entrada; ++i){ //recorro todo el set de datos
		
			vector<double> &entrada = datos[indices[i]]; //un patrón de entrada (no todas)

			//busco la ganadora para este patrón de entrada
			int iwin, jwin;
			competir(entrada, iwin, jwin);

			//actualizar los pesos
			actualizar_pesos(iwin, jwin, entrada, it);


			it++;
		}
	}

}
