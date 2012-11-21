#ifndef _FUNC_H_
#define _FUNC_H_

#include <string>
#include "genetic.h"

using namespace std;

/**
 * @file func.h Funciones auxiliares.
 */


/**
 * Representa un iterador en una cadena. De esta forma al trabajar con iteradores
 * se puede trabajar con subcadenas sin necesidad de crear objetos temporales.
 */
typedef string::const_iterator iterador;


int bin2dec(iterador inicio, iterador fin, bool neg);
double decode(iterador inicio, iterador fin, int A, bool neg);
double decode(const Cromosoma &c, int A, bool neg);
double func1(double x);
double var1(Cromosoma &c);
double fitness1(Individuo &i);
double func2(double x);
double var2(Cromosoma &c);
double fitness2(Individuo &i);
double func3(double x, double y);
pair<double, double> var3(Cromosoma &c);
double fitness3(Individuo &i);

//para gradiente descendiente:

typedef vector<double> X;

X descent(X &inicio, double (*der)(X&), int maxiter, double eta);
double derivada1(X &val);
double derivada2(X &val);
double derivada3(X &val);

#endif
