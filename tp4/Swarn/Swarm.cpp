#include "Swarm.h"
#include <ctime>
#include <cstdlib>
using namespace std;

Swarm::Swarm(int cant_p,int cant_v,double c1,double c2,bool overlaped,vector<pair<double,double> > rango, int v0) {
	srand(time(NULL));
	if(overlaped){ //si se desean vecindades solapadas
		
	}
	else{ //si no se desean vecindades solapadas
		int cantxv=cant_p/cant_v; //cantidad de particulas por vecindad
		for(int i=0;i<cant_v;i++) { 
			vector<Particula> A;
			for(int j=0;j<cantxv;j++) { 
				//aca podria cambiar c1 y c2 para hacerlo diferente para cada particula o cambiarlo arriba para que varie por cada vecindad 
				Particula P(c1,c2,rango,v0);
				A.push_back(P);
				}
			this->Enjambre.push_back(A);
			}
		//agregar los restantes a la ultima vecindad si cantxv no da exacto.
		}
	
	
	
	
	}
	
	


Swarm::~Swarm() {
	
}

