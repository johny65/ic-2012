#include "Swarm.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

void mostrar(vector<double> x){
	for(size_t i=0;i<x.size();i++) { 
		cout<<x[i]<<", ";
	}
}

Swarm::Swarm(int cant_p,int cant_v,double c1,double c2,vector<pair<double,double> > rango, int v0) {
	/**
	@param cant_p: cantidad de particulas
	@param cant_v: cantidad de vecindades
	@param c1: aceleracion respecto a la mejor pos personal
	@param c2: aceleracion respecto a la mejor pos local (vencindad)
	@param rango: rango de inicializacion x-min, xmax del problema extendible a n-dimensiones
	@param v0: intero entre 0-100 para realizar una inicializacion aletoria de la velocidad ~U(0,v0)
	*/
	srand(time(NULL));
	int cantxv=cant_p/cant_v; //cantidad de particulas por vecindad
	//cout<<"cant x vecindad "<<cantxv<<endl;
	for(int i=0;i<cant_v;i++) { 
			vector<Particula> A;
			for(int j=0;j<cantxv;j++) { 
				
				//aca podria cambiar c1 y c2 para hacerlo diferente para cada particula o cambiarlo arriba para que varie por cada vecindad 
				Particula P(c1,c2,rango,v0);
				A.push_back(P);
			}
			this->Enjambre.push_back(A);
		}
//
//		//agregar los restantes a la ultima vecindad si cantxv no da exacto.
		int parada=cantxv*cant_v;
		if(parada!=cant_p && this->Enjambre.at(0).size()!=cant_p){ 
			parada=cant_p-parada;
			for(int i=0; i<parada; i++){
				Particula P(c1,c2,rango,v0);
				this->Enjambre[i].push_back(P);
			}
		}

		

		
		//inicializo las mejores posiciones en las vecindades igual a la posicion de la primera particula en cada vecindad
		for(int i=0;i<cant_v;i++) { 
			this->bestxvec.push_back(this->Enjambre[i][0].get_Pos());
		}
		cout<<"Posiciones iniciales "<<endl;
		mostrar_posiciones();	
	}
Swarm::~Swarm() {
	
}

double Swarm::fitness(int id, vector<double> P){
	/**
	*@param id : identificacion de la funcion a optimizar
	*@param x y: valores en los cuales se evalua la funcion
	*@return z: el resultado de la evaluacion
	*/
	double z; ///<valor de retorno
	
	int x=P[0];
	
	
	switch(id){
	case 1: if(abs(x)>512) z=10000; else z=-x*sin(sqrt(abs(x)));
		break;
	case 2: z=x + 5*sin(3*x) + 8*cos(5*x);
		break;
	case 3: int y=P[1]; z= pow(pow(x,2)+pow(y,2),0.25)*(pow(sin(50*(pow(pow(x,2)+pow(y,2),0.1))),2)+1);
		break;
	}
	return z;
}

void Swarm::Volar(int max_it,int id){
	/**
	@param max_it: maximo num de iteraciones
	@param id: identificador de la funcion de fitness
	*/
	int i=0;
	vector<double> pos_a, best_pp;
	while (i<max_it){
		cout<<"iteracion "<<i+1<<endl;
		for(size_t j=0;j<this->Enjambre.size();j++) { 
			for(size_t k=0;k<this->Enjambre[j].size();k++) { 
				
				pos_a=this->Enjambre.at(j).at(k).get_Pos(); //posicion actual de la particula
				best_pp=this->Enjambre.at(j).at(k).get_best_pers(); //mejor posicion personal obtenida por la particula
				
				//Actualizo la mejor posicion personal de cada particula y calculo la mejor posicion en el vecindario
				if(fitness(id,pos_a)<fitness(id,best_pp)){
					
					//actualizo la posicion pesonal
					this->Enjambre[j][k].actualizar_best_pers(pos_a);
				}
				if(fitness(id,pos_a)<fitness(id,this->bestxvec[j])){
					//actualizo la mejor posicion local (en el vecindario)
					this->bestxvec[j]=pos_a;
				}
			}
		}
	
		for(size_t j=0;j<this->Enjambre.size();j++) { 
			for(size_t k=0;k<this->Enjambre[j].size();k++) { 
				//Actulizo la velocidad
				this->Enjambre[j][k].actualizar_vel(this->bestxvec[j]);
				//Actualizo la posicion
				this->Enjambre[j][k].actualizar_pos();
			}
		}
		
			mostrar_posiciones();
			i+=1;
		}
		
		cout<<"Posiciones finales "<<endl; mostrar_posiciones();
		for(int i=0;i<this->bestxvec.size();i++) { 
			mostrar(this->bestxvec.at(i));
		}
		///< to do: rutinas de graficacion
		///< to do: otra condicion de corte
		
	}


void Swarm::mostrar_posiciones(){
	for(size_t i=0;i<this->Enjambre.size();i++) { //recorro la vecindad
		for(size_t j=0;j<this->Enjambre[i].size();j++) {  //recorro las particulas de la vecindad i
			cout<<"Particula "<<j<<" ";
			mostrar(this->Enjambre[i][j].get_Pos());
			cout<<" fitness "<<fitness(1,this->Enjambre[i][j].get_Pos())<<endl;
			//cout<<endl<<"------------------"<<endl;
		}
	}
}
