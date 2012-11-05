#include "Particula.h"
#include <cstdlib>
#include "func.h"
#include <vector>
using namespace std;

Particula::Particula(double ac1,double ac2,vector<pair<double,double> > rango,int v0){
	/**
	* @param ac1: aceleracion c1;
	* @param ac2: aceleracion c2;
	* @param rango: vector que guarda el rango para cada variable i.e. para x: (x.first, x.second). para y: (y.first, y.second), etc
	* @param v0: para generar el rango de inciacializacion de la velocidad v~U(0,vo) v0 se pasa como un numero entre 0 y 100 y despues se lo pasa al rango [0 1]
	*/
	//incializo c1 y c2
	this->c1=ac1;
	this->c2=ac2;
	
	//inicializo r1 y r2
	r1=(0+rand()%100)/100.0;
	r2=(0+rand()%100)/100.0;
	
	//Inicializo las posiciones aletoriamente
	int dim=rango.size(); ///<dimension del problema a resolver
	
	//inicializo las posiciones en el rango correspondiente
	
	for(int i=0;i<dim;i++) { 
		int sep=abs(rango[i].second-rango[i].first);
		double p=rango[i].first+rand()%(sep);
		this->Pos.push_back(p);
	}
	
	//incializacion de la velocidad
	if(v0==0){//inicializo la velocidad igual a la posicion inicial
		this->Vel=this->Pos;
	}
	else{//incializo la velocidad con un numero aletorio entre 0 y v0
		for(int i=0;i<dim;i++) { 
			this->Vel.push_back((1+rand()%v0)/100.0);
		}
	}
	
	//Inicializo la mejor pos personal = a la posicion inicial
	this->best_pers=this->Pos;
	
	
}

Particula::~Particula() {
	
}


void Particula::actualizar_vel(vector<double> best_local){
	vector<double> dml=dif(this->best_pers,this->Pos);
	vector<double> dmg=dif(best_local,this->Pos);
	for(int i=0;i<this->Vel.size();i++) { 
		Vel[i]+=c1*r1*dml[i]+c2*r2*dmg[i];
	}
	
} 

void Particula::actualizar_pos(){
	for(int i=0;i<this->Pos.size();i++) { 
		Pos[i]+=Vel[i];
	}

}
void Particula::actualizar_best_pers(vector<double> &b){
	this->best_pers=b;
}

vector<double> Particula::get_Pos(){
	return this->Pos;
}

vector<double>Particula::get_best_pers(){
	return this->best_pers;
}

