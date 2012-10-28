#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include "genetic.h"
#include <algorithm>



using namespace std;

double func(int x)
{
    return -x * sin(sqrt(fabs(x)));
}

double fitness_func(int x)
{
    return -func(x);
}

void evaluar_fitness(Poblacion &p)
{
    for (size_t i=0; i<p.size(); ++i){
        p[i].fitness = fitness_func(bin2int(p[i].cromosoma));
    }
}

int main(){

    int maxiter = 100;
    Poblacion v = crear(100, 10);
    int it = 0;
    while (it < maxiter){
        evaluar_fitness(v);
        Poblacion nueva = seleccionar(v);
        for (int i=0; i<100; ++i){
            cruzar(v[rand()%100].cromosoma, v[rand()%100].cromosoma);
            mutar(v[rand()%100].cromosoma);
        }
        v = nueva;
        it++;
    }
    
    evaluar_fitness(v);
    sort(v.begin(), v.end());
    cout<<"Solución: "<<v[0].cromosoma<<endl<<bin2int(v[0].cromosoma)<<endl;

    return 0;
}
