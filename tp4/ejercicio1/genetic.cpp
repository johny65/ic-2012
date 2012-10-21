#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include "genetic.h"

using namespace std;

/**
 * @brief Crea una población aleatoria de `n` individuos de longitud `l`. Cada
 * individuo está representado por un cromosoma (cadena de genes).
 */
Poblacion crear(int n, int l)
{
    srand(time(NULL));
    Poblacion res(n);
    int r, i, j;
    Gen *s;
    for (i=0; i<n; ++i){
        s = new Gen[l+1];
        for (j=0; j<l; ++j){
            r = rand();
            s[j] = (r%2 ? '0' : '1');
        }
        s[l] = '\0';
        res[i] = s;
        delete[] s;
    }
    return res;
}


/**
 * @brief Cruza dos cromosomas.
 */
void cruzar(Cromosoma &a, Cromosoma &b)
{
    assert(a.size() == b.size());
    int l = a.size();
    int r = rand()%l; //locus aleatorio
    swap_ranges(a.begin()+r, a.end(), b.begin()+r);
}


/**
 * @brief Muta un cromosoma (intercambia un bit aleatorio).
 */
void mutar(Cromosoma &a)
{
    int r = rand()%a.size();
    a[r] = (a[r] == '0' ? '1' : '0');
}
