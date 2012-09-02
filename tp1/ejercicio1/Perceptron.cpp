#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Perceptron.h"
#include "utils.h"
#include "func.h"
#include "wait.h"
#include "GNUplot.h"

using namespace std;

/**
 * @brief Constructor por defecto.
 *
 * El constructor por defecto fija los parámetros del perceptrón (tasa de
 * aprendizaje, cantidad máxima de iteraciones, etc.) en valores predeterminados.
 * Para configurar estos parámetros se deben usar las funciones específicas.
 */
Perceptron::Perceptron() : eta(0.05), max_iter(1000), func(signo),
	tol(10e-3), graficos(true), tiempo_espera(500) {}


/**
 * @brief Destructor.
 */
Perceptron::~Perceptron() {}


/**
 * @brief Define el número máximo de iteraciones para entrenar el Perceptron.
 * @param m Cantidad máxima de iteraciones.
 */
void Perceptron::set_iteraciones_max(int m)
{
	this->max_iter = m;
}


/**
 * @brief Define la tolerancia del error.
 *
 * A medida que va entrenando el perceptrón, se calcula una medida del error
 * entre su salida y las salidas deseadas. Cuando este error sea menor que esta
 * tolerancia, el entrenamiento se detiene.
 *
 * @param t Nueva tolerancia.
 */
void Perceptron::set_tolerancia(double t)
{
	this->tol = t;
}


/**
 * @brief Establece el tiempo de espera entre frames para la animación, es
 * decir el tiempo que hay que esperar para dibujar otra vez.
 * @param t Tiempo de espera.
 */
void Perceptron::set_tiempo_espera(double t)
{
	this->tiempo_espera = t;
}


/**
 * @brief Establece si se deben mostrar los gráficos o no.
 * @param g true si se muestran gráficos, false si no.
 */
void Perceptron::set_graficos(bool g)
{
	this->graficos = g;
}


/**
 * @brief Rutina con la cual el Perceptron aprende a partir de datos.
 * @param name Nombre del archivo .csv a leer, el mismo contiene los datos de
 * entrenamiento.
 * @return (Andrés poné qué devuelve, antes era void)
 */
int Perceptron::entrenar(const char *name)
{
	
	vector< vector<double> > datos=leer_csv(name, this->salidas_deseadas);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo"<<endl;return -1;}
	vector<double> entradas;
	
	vector< vector<double> >::iterator q=datos.begin();
	this->nd=(*q).size(); //cantidad total de entradas (sesgo incluido)
	
	//archivo para gnuplot
	crear_dat(datos, "plot.dat");
	
	//inicializo el vector de pesos aletoriamente con valores entre [-0.5 0.5]
	this->pesos = init_weight(nd);
	
	double error_e;
	int iteraciones = 0;
	while (iteraciones < this->max_iter){
		salidas.clear();
		int i = 0;
		q=datos.begin();
		//cout<<endl<<"Pesos nuevos"<<endl; mostrar_pesos(); cout<<endl;
		error_e=0;
		
		while(q!=datos.end()){
			
			entradas = *q;
			this->salidas.push_back(clasificar(entradas));
			
			if(this->salidas_deseadas[i] != salidas.back()){ //salida deseada != salida obtenida?
				pesos=recalcular_pesos(this->pesos, this->eta,
					this->salidas.back(), this->salidas_deseadas[i], entradas);				
			}
			error_e+=calc_error_x_epoca(this->salidas_deseadas[i],this->salidas.back());
			//mostrar_pesos();
			if (this->graficos)
				graficar();
			//cout<<endl;
			
			q++; i++;
		}
		
		//calcular error por iteracion:
		double err = calc_error(this->salidas_deseadas, this->salidas);
		cout<<"Error: "<<err<<endl;
		
		if (err <= this->tol)
			break;
		
		iteraciones++;
		cout<<"Iteración "<<iteraciones<<endl;
	}
	
	this->error.push_back(error_e/datos.size()); //guardo el error
	this->weight.push_back(pesos); //guardo los pesos 
	
	cout<<"Se terminó de entrenar el perceptrón.\n"<<"iteraciones "<<iteraciones<<" error "<<error.back()<<endl;
	
	if (this->graficos)
		graficar();
	
	//Muestro el resultado del entrenamiento
	q=datos.begin();
	int g=0;
	while(q!=datos.end()){
		for (int i=0;i<(int)(*q).size();i++){
			cout<<setw(8)<<setprecision(3)<<(*q)[i];
		}
		cout<<"    |"<<setw(5)<<setprecision(3)<<salidas_deseadas[g];
		cout<<"    |"<<setw(5)<<setprecision(3)<<salidas[g]<<endl;
		g++;
		q++;
	}

	salidas.clear(); //borro los datos de las salidas el Perceptron ya esta entrenado
	return 0;
}

void Perceptron::probar(const char *name){
	
	/**
		@brief Rutina que a partir de los datos de prueba genera las salidas y grafica(idea falta implementar)
		@param datos matriz de datos de prueba en este vector no existe salida esperada a diferencia de la rutina entrenar
	*/
	vector<vector<double> > datos = leer_csv(name, this->salidas_deseadas);
	if(pesos.empty()) {cout<<"Primero debe entrenar el Perceptron"<<endl; return;}
	vector< vector<double> >::iterator q=datos.begin();
	
	while(q!=datos.end()){
		salidas.push_back(clasificar(*q));
		q++;
	}
	
	generar_resultados(datos,salidas,"resultadoprueba.txt");
	
}

//para qué es esta función? no se usa nunca
/*
void Perceptron::result(){
	vector<double>::iterator q=entradas.begin(), p=salidas.begin();
	cout<<"entradas:        "<< " salidas "<<endl<<"---------------------"<<endl;
	while(p!=salidas.end()){
		
		while(q!=entradas.end()){
			cout<<*q<<" ";
			q++;
		}
		p++;
	}
}
*/


/**
 * @brief Función para mostrar los pesos del perceptrón.
 */
void Perceptron::mostrar_pesos(){
	vector<double>::iterator q=this->pesos.begin();
	while(q!=pesos.end()){
		cout<<(*q)<<" , ";
		q++;
	}
	cout<<endl;
}


/**
 * @brief Fija la tasa de aprendizaje para el Perceptron.
 * @param n Tasa de aprendizaje nueva.
 */
void Perceptron::fijar_tasa(double n)
{
	this->eta = n;
}


/**
 * @brief Rutina que permite seleccionar la función del Perceptron.
 * @param x Es 1-función signo, 2-función sigmoide, 3-funcion gaussiana (esta es la idea->no esta implementado)
 */
void Perceptron::sel_func(int x){

	if (x == 1)
		this->func = signo;
	else if (x == 2)
		this->func = sigmoide;
	
}


/**
 * @brief Devuelve la salida que calcula el perceptrón para una entrada dada con los
 * pesos actuales.
 * @param D Vector con un patrón de entrada.
 * @return El valor de salida calculado.
 */
double Perceptron::clasificar(const vector<double> &D){
	return func(dot(D, this->pesos), 1.0);
}


/**
 * @brief Función para graficar.
 *
 * Esta función grafica, en el caso de entradas en 2 dimensiones, un plano y la
 * recta que van formando los pesos del perceptrón. En el caso de entradas con
 * 3 dimensiones, dibuja el plano que van formando los pesos del perceptrón.
 * Además también dibuja los puntos de las entradas.
 * 
 */
void Perceptron::graficar()
{
	double &w0 = pesos[0];
	double &w1 = pesos[1];
	double &w2 = pesos[2];

	///\todo hacer que dibuje los puntos de cada clase de distintos colores
	
	if(pesos.size()==3){ //gráfico en 2 dimensiones
		///<\todo acá no hace zoom ni con el click del medio!
		stringstream ss;
		ss<<"plot [-2:2] [-2:2]"<<-1*(w1/w2)<<"*x + "<<w0/w2;
		ss<<", \"plot.dat\" lt 3";
		plotter(ss.str());
		wait(this->tiempo_espera);
	}
	
	else if (pesos.size() == 4){ //gráfico en 3 dimensiones
		//Zoom con click del medio!
		double &w3 = pesos[3];
		stringstream ss;
		ss<<"splot [-2:2] [-2:2] [-2:2]"<<-1*(w2/w3)<<"*y + "<<-1*(w1/w3)<<"*x + "<<w0/w3;
		ss<<", \"plot.dat\" lt 3";
		plotter(ss.str());
		wait(this->tiempo_espera);
	}
}


void Perceptron::val_cross(){
	/**
	@brief esta rutina entrena el Perceptron con varias particiones, calcula el error, y escoge el menor de ellos
	
	
	*/
	
	vector<double> sal_esp;
	stringstream name;
	name<<"./particiones/particion_e1.csv";
	int i=2;
	while(entrenar((name.str()).c_str())==0){
		name.str("");
		name<<"./particiones/particion_e"<<i<<".csv";
		i++;
	}
	
	
	//Buscar segun el minimo error y actualizar el vector de pesos
	double menor=this->error[0];
	int ind_m=0;
	for (int i=1;i<this->error.size(); i++){
		if(menor>this->error[i]){ menor=this->error[i]; ind_m=i;}
	}
	this->pesos.clear();
	this->pesos=this->weight[ind_m];

	
	
	
}
