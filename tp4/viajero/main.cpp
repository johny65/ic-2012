#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <unistd.h>
#include "genetic.h"
#include "func.h"
#include "argparser.h"

#define print(v) copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));\
    cout<<endl


using namespace std;

int N; //cantidad de ciudades
vector< vector<double> > V; //matriz de distancias


double fitness(Individuo &I)
{
	Cromosoma &c = I.cromosoma;
	double f = 0.0;
	int ciudad_inicio = c[0];
	int ciudad_ant = ciudad_inicio;
	for (size_t i=1; i<c.size(); ++i){
		f += V.at(ciudad_ant).at(c[i]);
		ciudad_ant = c[i];
	}
	f += V.at(ciudad_inicio).at(ciudad_ant);
	//cout<<"f: "<<f<<endl;

	return -f;
}



int main(int argc, char **argv){

	srand(time(NULL) + getpid());
	char sN[] = "10"; //cantidad de ciudades por defecto

	ArgParserNew(parser);
	parser.opcion("N", 'n', "Cantidad de ciudades", sN);
	parser.opcion("maxiter", 'i', "Cantidad máxima de iteraciones", "100");
	parser.opcion("ind", 'c', "Cantidad de individuos", "100");
	parser.opcion("elite", 'e', "Elitismo", "1");
	parser.parsear(true);
	
	N = parser.get("N");

	set<int> ciudades;
	V = vector< vector<double> >(N, vector<double>(N, 0.0));

	/*
	int f = 0, c = 0, i = 0;
	while (i < N){
		f = c = i;
		while (f < N-1){
			f++;
			double d = rand()%100;
			V[f][i] = d;
			V[i][f] = d;
		}
		i++;
	}
	*/
	
	/*
	int c1, c2;
	double dist;
	while ((int)ciudades.size() != N){
		cin>>c1>>c2>>dist;
		ciudades.insert(c1);
		ciudades.insert(c2);
		V[c1][c2] = dist;
		V[c2][c1] = dist;
	}
	*/

	/*
	for (int f=0; f<N; ++f){
		for (int c=0; c<N; ++c){
			cout<<V[f][c]<<" ";
		}
		cout<<endl;
	}
	//*/


	//leer archivo:
	int c;
	double x1, x2;
	vector< pair<int, int> > coord(N);
	for (int i=0; i<N; ++i){
		cin>>c>>x1>>x2;
		coord[c] = make_pair(x1, x2);
	}
	for (int i=0; i<N; ++i){
		for (int j=0; j<N; ++j){
			V[i][j] = sqrt(pow(coord[i].first - coord[j].first, 2) +
				pow(coord[i].second - coord[j].second, 2));
		}
	}
	cout<<"Matriz armada.\n";
		
	cout<<"Cantidad de ciudades: "<<N<<endl;
	
	int maxiter = parser.get("maxiter");
	//int maxiter = 1000;
	cout<<"Cantidad máxima de iteraciones: "<<maxiter<<endl;
	
	int cantindividuos = parser.get("ind");
	//int cantindividuos = 100;
	cout<<"Cantidad de individuos: "<<cantindividuos<<endl;

	GA genetico(cantindividuos, N);
	
	//cout<<"Inited\n";
	genetico.setFuncionFitness(fitness);
	//cout<<"Fitness listo\n";
	genetico.setMaximasIteraciones(maxiter);
	genetico.Elitismo(parser.get("elite"));
	cout<<"Ejecutando...";cout.flush();

	Individuo ii;
	ii.cromosoma = genetico.Ejecutar();
		
	cout<<"Solución: "; print(ii.cromosoma);
	cout<<"Costo total: "<<-fitness(ii)<<endl;
	
	while (true){}
	return 0;
}
