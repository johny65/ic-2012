#ifndef SWARM_H
#define SWARM_H
#include <set>
#include <vector>
#include "Particula.h"
using namespace std;

class Swarm {
private:
	vector<vector<Particula> > Enjambre; ///<vector de conjunto de particulas para modelar las vecindades.
	vector<vector<double> > bestxvec; ///<vector que guarda el mejor por cada vecindario
public:
	Swarm(int cant_p,int cant_v,double c1,double c2,bool overlaped,vector<pair<double,double> > rango, int v0);
	~Swarm();
	double fitness(int id, vector<double> );
	void Volar(int,int); ///<rutina principal del programa
	
};

#endif

