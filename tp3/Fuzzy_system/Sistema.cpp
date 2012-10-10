#include "Sistema.h"
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
using namespace std;
Sistema::Sistema(int cant_conj,vector<double> intervalos_t,vector<double> intervalos_i,vector<double> intervalos_v) { 
	/**
	@param cant_conj: cantidad de conjuntos difusos.
	@param intervalos de los conjuntos difusos (el tamanio del vector debe ser 2*cant conjuntos contiene los valores left y right de los triangulos)
	*/
	//cargo los triangulos de entrada
	triangulo aux;
	for(int i=0;i<cant_conj;i++) { 
		aux.left=intervalos_t[2*i];
		aux.right=intervalos_t[2*i+1];
		aux.calcular_centro();
		this->conjuntos_temp.push_back(aux);
	}
	
	//genero conjuntos de salida de la corriente
	for(int i=0;i<cant_conj;i++){
		aux.left=intervalos_i[2*i];
		aux.right=intervalos_i[2*i+1];
		aux.calcular_centro();
		this->conjuntos_i.push_back(aux);
	}
	
	//genero conjuntos de salida del voltaje.
	for(int i=0;i<cant_conj;i++){
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
	crear_dat_conjuntos(this->conjuntos_temp,"conjuntos.dat");
	ostringstream sp;
	sp<<"plot \"conjuntos.dat\" with lines";
	plotter(sp.str());
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
	vector<int> indice_conj;
	double memb,ti;
	double c;///< aqui guardare el valor del centroide

	///<Rutina Principal
	///<calcular conjunto y grado de membresia de los conjuntos de entrada (guardo num_conjunto, grado_membresia);
	
	this->temp_int_cc.push_back(20); ///< to do provisorio. 
	///
	bool regla_i=false; ///< indica si tengo que usar la regla de inferencia de la corriente caso contrario uso la del voltaje
	for(int i=1;i<this->temp_ext.size();i++) {
		double *T=&(this->temp_int_cc[i-1]); ///< valor de la temperatura anterior
		///<calculo los conjuntos a los cuales pertenece y la membresia de los mismos
		for(int j=0;j<this->conjuntos_temp.size();j++) { 
			if(this->conjuntos_temp[j].pertenece(*T)){ ///< si pertenece al conjunto j calculo el grado de membresia
				memb=this->conjuntos_temp[j].calcular_degree(*T);
				if(j==1 || j==2) regla_i=true; ///<las inferencias se hacen sobre la tabla de corriente
				if(regla_i){
					//cout<<"entre en la corriente"<<endl;
					indice_conj.push_back(this->Temp_i.at(j));///<guardo el indice del conjunto de la corriente 
					//cout<<indice_conj.back()<<endl;
					conjuntos_i[indice_conj.back()].calcular_bc(memb); ///<calculo el trapezoide correspondiente con el mismo grado de membresia
				}
				else{
					indice_conj.push_back(this->Temp_v[j]);
					conjuntos_v[indice_conj.back()].calcular_bc(memb); ///<calculo el trapezoide correspondiente con el mismo grado de membresia
				}
			}
		}
		
		cout<<"temperatura de entrada "<<*T<<" indices"<<endl;
		for(size_t i=0;i<indice_conj.size();i++) { 
			cout<<indice_conj[i]<<endl;
		}
		//cout<<"LLego"<<endl;
		if(regla_i){ cout<<"llego"<<endl;
			c=calcular_centroide(conjuntos_i[indice_conj.at(0)].A,conjuntos_i[indice_conj.at(1)].A); cout<<c;
			if(this->puerta_abierta==i){
				ti=0.169*this->temp_int_cc.at(i-1)+0.831*this->temp_ext.at(i)+0.112*pow(c,2);
				this->temp_int_cc.push_back(ti);
				cout<<ti;
			}
			else{
				ti=0.912*this->temp_int_cc.at(i-1)+0.088*this->temp_ext.at(i)+0.604*pow(c,2);
				this->temp_int_cc.push_back(ti);
			}
		}
		else{
			c=calcular_centroide(conjuntos_v[indice_conj[0]].A,conjuntos_v[indice_conj[1]].A);
			if(this->puerta_abierta==i){
				ti=0.169*this->temp_int_cc.at(i-1)+0.831*this->temp_ext.at(i)-0.002*c;
				this->temp_int_cc.push_back(ti);
			}
			else{
				ti=0.912*this->temp_int_cc.at(i-1)+0.088*this->temp_ext.at(i)-0.1021*c;
				this->temp_int_cc.push_back(ti);
			}
		}
		//cout<<"LLego"<<endl;
		///termina una iteracion 
		regla_i=false; ///< la vuelvo a falso
		indice_conj.clear(); ///<borro los indices viejos
		
		
		
	
	}
}
