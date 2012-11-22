#include <iostream>
#include <iterator>
#include <cmath>
#include <set>
#include <map>
#include <utility>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <limits>
#include <unistd.h>
#include "genetic.h"
#include "utils.h"

#define print(v) copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));\
    cout<<endl

using namespace std;


/**
 * @brief Constructor.
 * @param n Cantidad de individuos que va a tener la población.
 * @param l Longitud de cada cromosoma.
 */
GA::GA(int n, int l) : itmax(100), pc(0.9), pm(0.1), elite(0),
	tipo_cruza(PartialMatchingCrossover)
{
    srand(time(NULL) + getpid());
    inicializar_poblacion(n, l);
}


/**
 * @brief Establece la cantidad máxima de iteraciones.
 */
void GA::setMaximasIteraciones(int it)
{
    this->itmax = it;
}


/**
 * @brief Función principal que ejecuta el algoritmo genético.
 */
Cromosoma GA::Ejecutar()
{
    int it = 0;
    int r1, r2;
    while (it < this->itmax){
        
        Poblacion nueva = seleccionar(this->poblacion);

        for (int i=0; i<this->N; ++i){
            r1 = rand()%this->N; r2 = rand()%this->N;
            if (rand()/RAND_MAX <= this->pc){
                cruzar(nueva[r1].cromosoma,
                    nueva[r2].cromosoma);
            }
            if (rand()/RAND_MAX <= this->pm){
                mutar(nueva[r1].cromosoma);
            }
            if (rand()/RAND_MAX <= this->pm){    
                mutar(nueva[r2].cromosoma);
            }
        }

        if (this->elite != 0) { //elitismo, agarrar los mejores y pasarlos directamente
            sort(this->poblacion.begin(), this->poblacion.end());
            for (int j=0; j<this->elite; ++j){
                nueva[j] = this->poblacion[j];
            }
        }
        
        this->poblacion = nueva;
        it++;

        if (!(it%1000)){
			cout<<"Fitness promedio: "<<this->f_promedio.back()<<endl;
		}
    }
    
    evaluar_fitness_poblacion();
    sort(this->poblacion.begin(), this->poblacion.end());

    graficar();
    
    return this->poblacion.front().cromosoma;
}


/**
 * @brief Crea una población aleatoria de `n` individuos de longitud `l`. Cada
 * individuo está representado por un cromosoma (cadena de genes).
 */
void GA::inicializar_poblacion(int n, int l)
{
    this->N = n;

    //recorrido inicial trivial: 0, 1, 2, ...
    Cromosoma c(l);
    for (int i=0; i<l; ++i)
		c[i] = i;
	Individuo canon; canon.cromosoma = c;

	//recorridos aleatorios:
	
    this->poblacion = Poblacion(n, canon);
	for (int i=0; i<this->N; ++i){
		Cromosoma &c = this->poblacion[i].cromosoma;
		random_shuffle(c.begin(), c.end());
	}
	
}


/**
 * @brief Cruza dos cromosomas.
 */
void GA::cruzar(Cromosoma &a, Cromosoma &b)
{
	assert(a.size() == b.size());
    int l = a.size();
	
	switch (this->tipo_cruza){
		
		case PartialMatchingCrossover: {

			int r1 = rand()%l, r2 = r1;
			while (r2 == r1)
				r2 = rand()%l;
			if (r2 < r1) swap(r1, r2);

			map<int, int> posa, posb;
			for (int i=0; i<l; ++i){
				posa.insert(make_pair(a[i], i));
				posb.insert(make_pair(b[i], i));
			}

			Cromosoma anuevo(a), bnuevo(b);

			int aux;
			for (int i=r1; i<=r2; ++i){
				aux = b[i];
				swap(anuevo[i], anuevo[posa[aux]]);
				aux = a[i];
				swap(bnuevo[i], bnuevo[posb[aux]]);
			}

			a = anuevo;
			b = bnuevo;

			break;
			
		}
		case OrderCrossover: {

			int r1 = rand()%(l+1), r2 = r1;
			while (r2 == r1)
				r2 = rand()%(l+1);
			if (r2 < r1) swap(r1, r2);

			//cout<<"A: "; print(a);
			//cout<<"B: "; print(b);
			//cout<<"r1: "<<r1<<" r2: "<<r2<<endl;
			
			int ib = r1+1, ia = r1+1;
			set<int> sa, sb;
			sa.insert(a.begin()+r1, a.begin()+r2);
			sb.insert(b.begin()+r1, b.begin()+r2);
			unsigned int ca = sa.size(), cb = sb.size();

			//Cromosoma temp(a.begin()+r1, a.begin()+r2);
			//cout<<"subcadena: "; print(temp);

			Cromosoma anuevo(l, -1), bnuevo(l, -1);
			copy(a.begin()+r1, a.begin()+r2, anuevo.begin()+r1);
			copy(b.begin()+r1, b.begin()+r2, bnuevo.begin()+r1);
			//cout<<"A nuevo: "; print(anuevo);
			
			for (int i=0; i<l; ++i){
				if (anuevo[i] < 0){
					while (sa.size() == ca){
						sa.insert(b.at(ib%l));
						ib++;
					}
					anuevo.at(i) = b.at((ib-1)%l);
					ca = sa.size();
				}
				if (bnuevo[i] < 0){
					while (sb.size() == cb){
						sb.insert(a.at(ia%l));
						ia++;
					}
					bnuevo.at(i) = a.at((ia-1)%l);
					cb = sb.size();
				}
				
			}

			a = anuevo;
			b = bnuevo;
			//cout<<"Nuevo A: "; print(anuevo);
			//cout<<"Nuevo B: "; print(b);
			//cin.get();
		}
	}
    
    //cin.get();
}


/**
 * @brief Muta un cromosoma (intercambia un bit aleatorio).
 */
void GA::mutar(Cromosoma &a)
{
    int r1 = rand()%a.size();
    int r2 = rand()%a.size();
    Cromosoma::iterator it = a.begin()+r1;
    int aux = *it;
    a.erase(it);
    a.insert(a.begin()+r2, aux);
}


/**
 * @brief Función de selección (por ahora sólo competencia).
 */
Poblacion GA::seleccionar(Poblacion &vieja)
{
    const int N = 5; //cantidad de individuos que compiten

    double maxfit = -numeric_limits<double>::max();
    int maxind = 0;

    evaluar_fitness_poblacion();
    Poblacion nueva(vieja.size());

    for (size_t i=0; i<nueva.size(); ++i){
        for (int j=0; j<N; ++j){
            int r = rand()%vieja.size();
            Individuo &seleccionado = vieja[r];
            if (seleccionado.fitness > maxfit){
                maxfit = seleccionado.fitness;
                maxind = r;
            }
        }
        nueva[i] = vieja[maxind];
    }

    return nueva;
}


/**
 * @brief Evalúa el fitness de cada individuo de la población.
 */
void GA::evaluar_fitness_poblacion()
{
    double fmin = numeric_limits<double>::max();
    double fmax = -numeric_limits<double>::max();
    double sum = 0.0;
    
    for (int i=0; i<this->N; ++i){
        this->poblacion[i].fitness = fitness_func(
            this->poblacion[i]);
        if (this->poblacion[i].fitness < fmin) fmin = this->poblacion[i].fitness;
        if (this->poblacion[i].fitness > fmax) fmax = this->poblacion[i].fitness;
        sum += this->poblacion[i].fitness;
    }

    //guada mejor, promedio y peor:
    this->f_mejor.push_back(fmax);
    this->f_peor.push_back(fmin);
    this->f_promedio.push_back(sum/this->N);
    
}


/**
 * @brief Establece la función de fitness a usar para evaluar la población.
 * @param f Función de fitness, debe aceptar como parámetro un Individuo&.
 */
void GA::setFuncionFitness(double (*f)(Individuo&))
{
    this->fitness_func = f;
}


/**
 * @brief Uso de elitismo en el algoritmo (el mejor o los n mejores se
 * mantienen tras generación).
 * 
 * @param n Cantidad de individuos que pasan directamente a la siguiente
 * generación. Si es 0 no hay elitismo.
 */
void GA::Elitismo(int n)
{
    this->elite = n;
}


/**
 * @brief Realiza el gráfico del mejor fitness, fitness promedio y peor
 * fitness a lo largo de las generaciones.
 */
void GA::graficar()
{
    crear_dat_vector(f_mejor, "fmejor.dat");
    crear_dat_vector(f_peor, "fpeor.dat");
    crear_dat_vector(f_promedio, "fprom.dat");
    plotter("plot \"fmejor.dat\" with lines");
    plotter("replot \"fpeor.dat\" with lines");
    plotter("replot \"fprom.dat\" with lines");
}
