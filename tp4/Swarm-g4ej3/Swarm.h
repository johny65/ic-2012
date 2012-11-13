#ifndef SWARM_H
#define SWARM_H

#include <vector>
#include "Particula.h"
#include "GNUplot.h"
#include <set>
using namespace std;

class Swarm {
private:
	vector<Particula>  Enjambre; ///<vector de conjunto de particulas para modelar las vecindades.
	vector<int> bestxvec; ///<vector que guarda el mejor por cada vecindario
	vector<double> func_obj; ///<vector que guarda todos los fitness 
	vector<set<int> > Vecindad;
	void mejores_de_vecindad(int id);
	void graficar(int id);
	GNUplot plotter;
	void mejores_pos_vecindad(int);
public:
	Swarm(int cant_p,int cant_v,double c1,double c2,vector<pair<double,double> > rango, int v0, int overlap);
	~Swarm();
	double fitness(int id, vector<double> );
	void Volar(int,int,bool); ///<rutina principal del programa
	void mostrar_posiciones(int);
	void mostrar_mejor_vecindad(int id);
};

#endif

