#ifndef _GENETIC_H_
#define _GENETIC_H_

#include <vector>
#include <string>
#include "GNUplot.h"

using namespace std;

/**
 * @file genetic.h
 * @brief Funciones para algoritmos genéticos.
 *
 * Cada cromosoma es un vector de valores enteros.
 */

typedef vector<int> Cromosoma;


/**
 * @class Individuo
 * Clase que representa un individuo de la población. Posee un cromosoma y un
 * valor real que indica su fitness.
 * Tiene sobrecargado el operador < para poder ordenar vectores de individuos
 * de acuerdo a su fitness (de mejor fitness a peor fitness).
 */
class Individuo {
public:
    Cromosoma cromosoma;
    double fitness;
    
    Individuo() : fitness(0.0) {}
    bool operator< (const Individuo &i) const { return fitness > i.fitness; }
};

typedef vector<Individuo> Poblacion;


enum TipoCruza {
	PartialMatchingCrossover,
	OrderCrossover
};

/**
 * @class GA
 * Clase principal para ejecutar el algoritmo genético.
 */
class GA {
private:
    Poblacion poblacion; ///< Población de individuos
    int N; ///< Cantidad de individuos en la población
    int itmax; ///< Cantidad máxima de iteraciones
    double pc, pm; ///< Probabilidad de cruza y mutación
    int elite; ///< Cantidad de individuos que pasan directamente
    TipoCruza tipo_cruza; ///< Operador de cruza

    void inicializar_poblacion(int n, int l);
    void evaluar_fitness_poblacion();
    void cruzar(Cromosoma &a, Cromosoma &b);
    void mutar(Cromosoma &a);
    Poblacion seleccionar(Poblacion &vieja);
    double (*fitness_func)(Individuo&); ///< Función de fitness

    //para gráficos:
    GNUplot plotter;
    vector<double> f_mejor, f_promedio, f_peor;
    void graficar();
    
public:
    GA(int n, int l);
    void setFuncionFitness(double (*f)(Individuo&));
    void setMaximasIteraciones(int it);
    void Elitismo(int n);
    Cromosoma Ejecutar();
};

    
#endif