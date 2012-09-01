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
	tol(10e-3), tiempo_espera(0.5) {}


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
	@brief Rutina con la cual el Perceptron aprende a partir de datos.
	@param name Nombre del archivo .csv a leer, el mismo contiene los datos de entrenamiento.
*/
int Perceptron::entrenar(const char *name){
	
	vector<vector<double> > datos=leer_csv(name, this->salidas_deseadas);
	if(datos.empty()) {cout<<"no se pudo leer el archivo"<<endl;return -1;}
	
	vector<vector<double> >::iterator q=datos.begin();
	nd=(*q).size(); //cantidad total de entradas (sesgo incluido)
	
	//archivo para gnuplot
	crear_csv(datos, "plot.dat");
	
	
	//inicializo el vector de pesos aletoriamente con valores entre [-0.5 0.5]
	double error_e;
	double tol;
	int iteraciones = 0;
	this->pesos=init_weight(nd);
	while (iteraciones < this->max_iter){
		salidas.clear();
		int i = 0;
		q=datos.begin();
		//Calculo la sumatoria (pasar siempre en dot en segundo lugar los pesos)
		cout<<endl<<"Pesos nuevos"<<endl; mostrar_pesos(); cout<<endl;
		error_e=0;
		
		while(q!=datos.end()){
			
			this->entradas = *q;
			this->salidas.push_back(func(dot(this->entradas,pesos), 1.0)); //ver ese 1.0...
			
			if(this->salidas_deseadas[i]!=salidas.back()){ //salida deseada != salida obtenida?
				tol+=1; //cuenta la cantidad salidas fallidas (criterio de parada)
				pesos=recalcular_pesos(this->pesos, this->eta,
					this->salidas.back(), this->salidas_deseadas[i], this->entradas);
				
			}
			error_e+=calc_error_x_epoca(this->salidas_deseadas[i],this->salidas.back());
			mostrar_pesos();
			graficar();
				cout<<endl;
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
	
	graficar();
	
	//Muestro el resultado del entrenamiento
	q=datos.begin();
	int g=0;
	while(q!=datos.end()){
		for (int i=0;i<(int)(*q).size();i++){
			cout<<setw(5)<<(*q)[i];
		}
		cout<<"    |"<<setw(5)<<salidas_deseadas[g];
		cout<<"    |"<<setw(5)<<salidas[g]<<endl;
		g++;
		q++;
	}

	salidas.clear(); //borro los datos de las salidas el Perceptron ya esta entrenado
	return 0;
}

void Perceptron::probar(const char *name){
	
	vector<vector<double> > datos = leer_csv(name, this->salidas_deseadas);
	/**
		@brief Rutina que a partir de los datos de prueba genera las salidas y grafica(idea falta implementar)
		@param datos matriz de datos de prueba en este vector no existe salida esperada a diferencia de la rutina entrenar
	*/
	if(pesos.empty()) {cout<<"Primero debe entrenar el Perceptron"<<endl; return;}
	vector< vector<double> >::iterator q=datos.begin();
	
	while(q!=datos.end()){
		salidas.push_back(clasificar(*q));
		q++;
	}
	
	generar_resultados(datos,salidas,"resultadoprueba.txt");
	
}
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


void Perceptron::mostrar_pesos(){
	vector<double>::iterator q=pesos.begin();
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


void Perceptron::sel_func(int x){
	/**
	@brief rutina que permite seleccionar la funcion del Perceptron
	@param x es 1-funcion signo, 2-funcion sigmoide, 3-funcion gaussiana (esta es la idea->no esta implementado)
	*/
	if (x == 1)
		this->func = signo;
	else if (x == 2)
		this->func = sigmoide;
	
}

double Perceptron::clasificar(vector<double> &D){
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
	
	//Zoom con click del medio!
	
	if(pesos.size()==3){
		stringstream ss;
		ss<<"set xlabel \"eje X\" \n";
		plotter(ss.str());
		ss<<"set ylabel \"eje Y\" \n";
		plotter(ss.str());
		ss<<"plot [-2:2] [-2:2]"<<-1*(w1/w2)<<"*x + "<<w0/w2;
		ss<<", \"plot.dat\" lt 3";
		plotter(ss.str());
		//sleep(0.5);
		wait(this->tiempo_espera);
	}
	
	else {

		double &w3 = pesos[3];
		
		stringstream ss;
		ss<<"set xlabel \"eje X\" \n";
		plotter(ss.str());
		ss<<"set ylabel \"eje Y\" \n";
		plotter(ss.str());
		ss<<"set zlabel \"eje Z\" \n";
		plotter(ss.str());
		ss<<"splot [-2:2] [-2:2] [-2:2]"<<-1*(w2/w3)<<"*y + "<<-1*(w1/w3)<<"*x + "<<w0/w3;
		plotter(ss.str());
		ss<<", \"plot3.dat\" lt 3";
		plotter(ss.str());
		//sleep(0.5);
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
