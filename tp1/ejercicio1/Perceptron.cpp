#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Perceptron.h"
#include "utils.h"
#include "func.h"

using namespace std;

Perceptron::Perceptron(double t=0.05) : mu(t), func(signo) {};

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
	vector<vector<double> > datos=leer_csv(name);
	vector<vector<double> >::iterator q=datos.begin();
	nd=(*q).size()-1; //numero de datos de entrada (el ultimo dato es la salida esperada)
	
	//inicializo el vector de pesos aletoriamente con valores entre [-0.5 0.5]
	int tol;
	pesos=init_weight(nd);
	do{
		salidas.clear();
		q=datos.begin(); tol=0;
		//Calculo la sumatoria (pasar siempre en dot en segundo lugar los pesos)
		cout<<endl<<"Pesos nuevos"<<endl; mostrar_pesos(); cout<<endl;
		while(q!=datos.end()){
			vector <double> d((*q).begin(),(*q).end()-1); d.push_back(-1);
			
			salidas.push_back(func(dot(d,pesos), 1.0)); //ver ese 1.0...
			
			if((*q)[nd]!=salidas.back()){ 
				tol+=1; //cuenta la cantidad salidas fallidas (criterio de parada)

				/* no entiendo este if... */
				
				if((*q)[nd]==1)  pesos=recalcular_pesos(pesos,2*mu,salidas.back(),(*q)[nd],d);
				else pesos=recalcular_pesos(pesos,2*mu,salidas.back(),(*q)[nd],d);
			}
			mostrar_pesos();cout<<endl;
			q++;
		}
	}while(tol>0);
	
	
	//Muestro el resultado del entrenamiento
	q=datos.begin();
	int g=0;
	while(q!=datos.end()){
		for (int i=0;i<(int)(*q).size();i++){
			cout<<(*q)[i]<<"   ";
		}
		cout<<salidas[g]<<endl;
		g++;
		q++;
	}
	salidas.clear(); //borro los datos de las salidas el Perceptron ya esta entrenado
	
}

void Perceptron::probar(const char *name){
	salidas.clear();
	vector<vector<double> > datos=leer_csv(name);
	/**
		@brief Rutina que a partir de los datos de prueba genera las salidas y grafica(idea falta implementar)
		@param datos matriz de datos de prueba en este vector no existe salida esperada a diferencia de la rutina entrenar
	*/
	if(pesos.empty()) {cout<<"Primero debe entrenar el Perceptron"<<endl; return;}
	vector<vector<double> >::iterator q=datos.begin();
	
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

void Perceptron::fijar_tasa(double m){
	this->mu = m;
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

void Perceptron::graficar(){
//	//archivo de salida de datos
//	ofstream data("data.txt");
//	
//	//guardamos los datos de prueba
//	vector<double> >::iterator q=entradas.begin();
//	while(q!=entradas.end()){
//		data<<(*q)[0]<<"\t"<<(*q)[1]<<endl;	
//		q++;
//	}
//	data.flush();
	
	plot("p \"data.txt\"");
}

int Perceptron::clasificar(vector<double> &D){
	entradas=D;
	entradas.push_back(-1);
	return (signo(dot(entradas,pesos)));
	
}
