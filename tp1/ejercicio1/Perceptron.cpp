#include "Perceptron.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "GNUplot.h"
#include "func.h"
using namespace std;





Perceptron::~Perceptron() {
	
}


void Perceptron::entrenar(vector<vector<double> > &datos){
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
			salidas.push_back(signo(dot(d,pesos)));
			if((*q)[nd]!=salidas.back()){ 
				tol+=1; //cuenta la cantidad salidas fallidas (criterio de parada)
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

void Perceptron::result(){
	vector<double>::iterator q=entradas.begin(), p=salidas.begin();
	while(p!=salidas.end()){
		cout<<"entradas:        ";
		while(q!=entradas.end()){
			cout<<*q<<" ";
			q++;
		}
		cout<<endl<<"salida "<<*p<<endl;
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
	mu=m;
}

void Perceptron::sel_func(int x){
	if(x>=1 &&x<=3) func=x;
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
void Perceptron::clasificar(vector<double> &D){
	entradas=D;
	D.push_back(-1);
	salidas.push_back(signo(dot(D,pesos)));
	
}
