#include "Sistema.h"
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
using namespace std;
Sistema::Sistema(vector<double> intervalos_t,vector<double> intervalos_i,vector<double> intervalos_v) { 
	/**
	@param cant_conj: cantidad de conjuntos difusos.
	@param intervalos de los conjuntos difusos (el tamanio del vector debe ser 2*cant conjuntos contiene los valores left y right de los triangulos)
	*/
	//cargo los triangulos de entrada
	triangulo aux;
	
	 
	//cargo los triangulos:
	for(int i=0;i<(intervalos_t.size()/2);i++) { 
		aux.left=intervalos_t[2*i];
		aux.right=intervalos_t[2*i+1];
		aux.calcular_centro();
		this->conjuntos_temp.push_back(aux);
	}
	
	//cargo un ultimo medio triangulo
	aux=this->conjuntos_temp.back();
	double l=aux.center; //el left del medio triangulo debe ser igual al center de ultimo cargado
	aux.left=l; aux.center=aux.right;
	this->conjuntos_temp.push_back(aux); //meto el ultimo medio triangulo, el right no me preocupa pues solo uso left y center;
	
	
	//genero conjuntos de salida de la corriente
	
	//cargo los triangulos:
	for(int i=0;i<(intervalos_i.size()/2);i++) { 
		aux.left=intervalos_i[2*i];
		aux.right=intervalos_i[2*i+1];
		aux.calcular_centro();
		this->conjuntos_i.push_back(aux);
	}
	
	//genero conjuntos de salida del voltaje.
	
	
	//cargo los triangulos:
	for(int i=0;i<(intervalos_v.size()/2);i++) { 
		aux.left=intervalos_v[2*i];
		aux.right=intervalos_v[2*i+1];
		aux.calcular_centro();
		this->conjuntos_v.push_back(aux);
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
	
	
	//Aca hago los mapeos se me ocurrio hacerlos asi (ver bien despues) se adjunta una planilla con las correspondecias.
	this->Temp_i[0]=3; this->Temp_i[1]=2; this->Temp_i[2]=1;
	this->Temp_v[2]=2; this->Temp_v[3]=3; this->Temp_v[4]=4;
	
	
	graficar_conjuntos();
}

Sistema::~Sistema() {
	
}

void Sistema::Simular_sincontrol(){
	this->temp_int_sc.push_back(20); ///<declaro la temperatura del interior inicial en 20 grados (solo para simular)
	for(int i=1;i<this->temp_ref.size();i++) {  
		if(i==this->puerta_abierta)
			this->temp_int_sc.push_back(0.169*this->temp_int_sc[i-1]+0.831*this->temp_ext[i]);
		else
			this->temp_int_sc.push_back(0.912*this->temp_int_sc[i-1]+0.088*this->temp_ext[i]);
	}
	graficar(this->temp_int_sc);
}

void Sistema::graficar_conjuntos(){
	crear_dat_conjuntos(this->conjuntos_temp,"conjunto_t.dat");
	crear_dat_conjuntos(this->conjuntos_i,"conjunto_i.dat");
	crear_dat_conjuntos(this->conjuntos_v,"conjunto_v.dat");
	///<to do Graficar con GNUPLOT
}

void Sistema::graficar(vector<double> &T){
	crear_dat_vector(T,"sin_control.dat");
	ostringstream sp;
	crear_dat_vector(this->temp_ext,"temp_ext.dat");
	sp<<"plot \"sin_control.dat\" with lines"<<"\n";
	sp<<"replot \"temp_ext.dat\" with lines"<<"\n";
	plotter(sp.str());
	
}

void Sistema::Simular_concontrol(){
	///< Para la simulacion hacemos lo siguiente:
	///< tomamos la temperatura de refencia y la restamos de la temperatura exterior(entrada) Text-Tr=n
	///< Si n<0 tengo que prender la calefaccion (i:corriente)
	///< Si n>0 tengo que prender la refrigeracion (v: voltaje);
	
	
}
