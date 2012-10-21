#ifndef _GENETIC_H_
#define _GENETIC_H_

#include <vector>
#include <string>

using namespace std;

/**
 * @file genetic.h
 * @brief Funciones para algoritmos genéticos.
 *
 * Cada cromosoma es un string (cadena de caracteres, donde cada caracter sería
 * un gen). La población es un vector de strings.
 * Las funciones están hechas asumiendo que los alelos disponibles son '0' y '1'
 * (es decir cadenas binarias).
 */
 
typedef char Gen;
typedef string Cromosoma;
typedef vector<Cromosoma> Poblacion;

Poblacion crear(int n, int l);
void cruzar(Cromosoma &a, Cromosoma &b);
void mutar(Cromosoma &a);

#endif