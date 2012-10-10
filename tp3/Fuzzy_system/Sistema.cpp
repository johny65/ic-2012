#include "Sistema.h"
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
using namespace std;
Sistema::Sistema(int cant_conj,vector<double> intervalos) { 
	/**
	@param cant_conj: cantidad de conjuntos difusos.
	@param intervalos de los conjuntos difusos (el tamanio del vector debe ser 2*cant conjuntos contiene los valores left y right de los triangulos)
	*/
	//cargo los triangulos
	triangulo aux;
	for(int i=0;i<cant_conj;i++) { 
		aux.left=intervalos[2*i];
		aux.right=intervalos[2*i+1];
		aux.calcular_centro();
		this->conjuntos.push_back(aux);
	}
	
	//inicializo la temperatura exterior segun la figura que esta en la guia cada 10 minuto cambia cada valor representa 10 segundos
	for(int i=0;i<6;i++) { 
		double t_ext=10+rand()%30;
		for(int j=0;j<60;j++) { //constante durante 10 minutos;
			this->temp_ext.push_back(t_ext);
		}
	}
	
	
	//inicializo la temperatura de referencia
	for(int i=0;i<6;i++) { 
		for(int j=0;j<60;j++) {//cada 10 minutos cambia la temperatura 
			this->temp_ref.push_back(i%2==0 ? 18 : 22);
		}
		cout<<this->temp_ref.back()<<setw(5);
	}
	
	//elijo un numero aletorio entre 0 y 359 instante en el cual se habre la puerta;
	this->puerta_abierta=0+rand()%360;
	
	graficar_conjuntos();
}

Sistema::~Sistema() {
	
}

void Sistema::Simular_sincontrol(){
	this->temp_int_sc.push_back(20); ///<declaro la temperatura del interior inicial en 20 grados (solo para simular)
	for(size_t i=1;i<this->temp_ref.size();i++) {  
		if(i==puerta_abierta)
			this->temp_int_sc.push_back(0.169*this->temp_int_sc[i-1]+0.831*this->temp_ext[i]);
		else
			this->temp_int_sc.push_back(0.912*this->temp_int_sc[i-1]+0.088*this->temp_ext[i]);
	}
	graficar(this->temp_int_sc);
}

void Sistema::graficar_conjuntos(){
	crear_dat_conjuntos(this->conjuntos,"conjuntos.dat");
	std::ostringstream sp;
	sp<<"plot conjuntos.dat";
	this->plotter(sp.str());
}

void Sistema::graficar(vector<double> &T){
	crear_dat_vector(T,"sin_control.dat");
	std::ostringstream sp;
	sp<<"plot sin_control.dat";
	this->plotter(sp.str());
	crear_dat_vector(this->temp_ext,"temp_ext.dat");
}

void Sistema::Simular_concontrol(){
	map<int,double> conj_memb; ///< la llave sera el indice del conjunto al que pertenece y el double el grado de membresia de ese conjunto
	double memb;
	///<Rutina Principal
	///<calcular conjunto y grado de membresia de los conjuntos de entrada (guardo num_conjunto, grado_membresia);
	
	///
	for(size_t i=0;i<this->temp_ext.size();i++) {
		double *T=&(this->temp_ext[i]); ///< valor de la temperatura exterior
		///<calculo los conjuntos a los cuales pertenece y la membresia de los mismos
		for(size_t j=0;j<this->conjuntos.size();j++) { 
			memb=this->conjuntos[j].calcular_degree(*T);
			if(memb!=-1){
				///<guardo el indice del conjunto(j) y la membresia
				conj_memb[j]=memb;
			}
		}
		///En este punto tengo en conj_memb (conj,grado_memb) correspondiente a la Temperatura T.
		
		///Aqui van los mapeos al conjunto de salida.
		
	}
	
}
