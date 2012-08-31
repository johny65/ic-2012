#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Perceptron.h"
#include "utils.h"
#include "func.h"
#include "wait.h"
#include "GNUplot.h"
#include <sstream>
using namespace std;

Perceptron::Perceptron(double t=0.05) : eta(t), func(signo),
	max_iter(1000), tol(10e-3) {};

Perceptron::~Perceptron() {}

void Perceptron::def_epocas (int g) {
	/**
		@brief define el numero max de iteraciones para entrenar el Perceptron
		@param g numero maximo de epocas.
	*/
	epocas=g;
	
}

void Perceptron::entrenar(const char *name){
	/**
	@brief rutina con la cual el Perceptron aprende a partir de datos
	@param name nombre del archivo .csv a leer, el mismo contiene los datos de entrenamiento.
	*/
	vector<vector<double> > datos=leer_csv(name, this->salidas_deseadas);
	vector<vector<double> >::iterator q=datos.begin();
	nd=(*q).size(); //cantidad total de entradas (sesgo incluido)

	//archivo para gnuplot
	crear_csv(datos, "plot.dat");
	
	
	//inicializo el vector de pesos aletoriamente con valores entre [-0.5 0.5]
	double tol;
	int iteraciones = 0;
	this->pesos=init_weight(nd);
	while (iteraciones < this->max_iter){
		salidas.clear();
		int i = 0;
		q=datos.begin(); tol=0;
		//Calculo la sumatoria (pasar siempre en dot en segundo lugar los pesos)
		cout<<endl<<"Pesos nuevos"<<endl; mostrar_pesos(); cout<<endl;

		
		while(q!=datos.end()){

			this->entradas = *q;
			this->salidas.push_back(func(dot(this->entradas,pesos), 1.0)); //ver ese 1.0...
			
			if((*q)[nd]!=salidas.back()){ //salida deseada == salida obtenida?
				tol+=1; //cuenta la cantidad salidas fallidas (criterio de parada)
				pesos=recalcular_pesos(this->pesos, this->eta,
					this->salidas.back(), this->salidas_deseadas[i], this->entradas);
				
			}
			
			mostrar_pesos();
			//armar_recta(this->pesos);		
			armar_plano(this->pesos);		
			cout<<endl;
			q++; i++;
		}

		//calcular error:
		double err = calc_error(this->salidas_deseadas, this->salidas);
		cout<<"Error: "<<err<<endl;

		if (err <= this->tol)
			break;
		
		iteraciones++;
		cout<<"Iteración "<<iteraciones<<endl;
	}
	cout<<"Se terminó de entrenar el perceptrón.\n";
	
	//Muestro el resultado del entrenamiento
	q=datos.begin();
	int g=0;
	while(q!=datos.end()){
		for (int i=0;i<(int)(*q).size();i++){
			cout<<(*q)[i]<<"   ";
		}
		cout<<" | "<<salidas_deseadas[g];
		cout<<" | "<<salidas[g]<<endl;
		g++;
		q++;
	}
	salidas.clear(); //borro los datos de las salidas el Perceptron ya esta entrenado
	
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

void Perceptron::fijar_tasa(double n){
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

void Perceptron::armar_recta(vector<double> &pesos)
{
	double &w0 = pesos[0];
	double &w1 = pesos[1];
	double &w2 = pesos[2];

	///<\Zoom con click del medio
	stringstream ss;
	ss<<"set xlabel \"eje X\" \n";
	plotter(ss.str());
	ss<<"set ylabel \"eje Y\" \n";
	plotter(ss.str());
	ss<<"plot [-2:2] [-2:2]"<<-1*(w1/w2)<<"*x + "<<w0/w2;
	plotter(ss.str());
	ss.str(""); ss<<"replot \"plot.dat\" lt 3";
	plotter(ss.str());
	//sleep(0.5);
	wait(0.5);
}

void Perceptron::armar_plano(vector<double> &pesos)
	
{
	double &w0 = pesos[0];
	double &w1 = pesos[1];
	double &w2 = pesos[2];
	double &w3 = pesos[3];
	
	///<\Zoom con click del medio
	
	stringstream ss;
	ss<<"set xlabel \"eje X\" \n";
	plotter(ss.str());
	ss<<"set ylabel \"eje Y\" \n";
	plotter(ss.str());
	ss<<"set zlabel \"eje Z\" \n";
	plotter(ss.str());
	ss<<"splot [-2:2] [-2:2] [-2:2]"<<-1*(w2/w3)<<"*y + "<<-1*(w1/w3)<<"*x + "<<w0/w3;
	plotter(ss.str());
	ss.str(""); ss<<"replot \"plot3.dat\" lt 3";
	plotter(ss.str());
	//sleep(0.5);
	wait(0.5);
}
/*void particionar(vector<vector<double> entradas,int cant, float porc){
	
}*/
