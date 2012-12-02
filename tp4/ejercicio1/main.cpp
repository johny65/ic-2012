#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>
#include "genetic.h"
#include "func.h"
#include "argparser.h"

using namespace std;

int main(int argc, char **argv){

	ArgParserNew(parser);
	parser.opcion("maxiter", 'i', "Cantidad máxima de iteraciones", "100");
	parser.opcion("ind", 'n', "Cantidad de individuos", "10");
	parser.opcion("elite", 'e', "Elitismo", "1");
	parser.opcion("func", 'f', "Función a probar", "1");
    parser.opcion("pc", 'c', "Probabilidad de cruza", "0.9");
    parser.opcion("pm", 'm', "Probabilidad de mutación", "0.1");
    parser.opcion("eta", 'd', "Constante para el gradiente descendiente", "0.2");
    parser.opcion_bool("graf", 'g', "Graficar función");
	parser.parsear(true);
    
    int maxiter = parser.get("maxiter");
    int N = parser.get("ind");
    int elite = parser.get("elite");
    int funcnum = parser.get("func");
    double pc = parser.get_double("pc");
    double pm = parser.get_double("pm");

    GNUplot p;
    bool graf = parser.is("graf");

    int L; //longitud del cromosoma
    double (*f)(Individuo&); //puntero a función de fitness
    
    switch (funcnum) {
        case 1: {
            /*
             * Función 1. Codificación:
             * 
             * Longitud total del cromosoma: 20 bits.
             * 10 bits para la parte entera (de -512 a 512) y 10 bits para parte
             * decimal.
             */
            L = 20;
            f = fitness1;
            if (graf)
                p("plot [-512:512] -x * sin(sqrt(abs(x)))");
            break;
        }
        case 2: {
            /*
             * Función 2. Codificación:
             *
             * Longitud total del cromosoma: 15 bits.
             * 5 bits para la parte entera (de 0 a 31) y 10 bits parte decimal.
             */
            L = 15;
            f = fitness2;
            if (graf)
                p("plot [0:20] x + 5*sin(3*x) + 8*cos(5*x)");
            break;
        }
        case 3: {
            /*
             * Función 3. Codificación:
             *
             * 2 valores reales pegados.
             * 8 bits parte entera (7 -> 128, 8 para -128,128)
             * 10 bits decimal
             * total l = 8+10+8+10 = 18+18 = 36
             */
            L = 36;
            f = fitness3;
            if (graf){
                string s = "set isosamples 100,100\n";
                s += "set hidden3d\n";
                s += "splot [-100:100][-100:100] (x**2 + y**2)**0.25 * ( sin(50 * (x**2+y**2)**0.1)**2 + 1)\n";
                p(s);
            }
            break;
        }
    }

    GA genetico(N, L);
    genetico.setProbabilidadCruza(pc);
    genetico.setProbabilidadMutacion(pm);
    genetico.setFuncionFitness(f);
    genetico.setMaximasIteraciones(maxiter);
    genetico.Elitismo(elite);
    
    cout<<"Ejecutando...";
    cout<<"Función: "<<funcnum<<endl;
	cout<<"Cantidad máxima de iteraciones: "<<maxiter<<endl;
	cout<<"Cantidad de individuos: "<<N<<endl;
	
    
    Individuo ii; ii.cromosoma = genetico.Ejecutar();
    double r = -f(ii);
    cout<<"Solución: "<<r<<endl;

    switch (funcnum) {
        case 1: {
            cout<<"Valor de x: "<<var1(ii.cromosoma)<<endl;
            break;
        }
        case 2: {
            cout<<"Valor de x: "<<var2(ii.cromosoma)<<endl;
            break;
        }
        case 3: {
            pair<double, double> val = var3(ii.cromosoma);
            cout<<"En el punto ("<<val.first<<", "<<val.second<<")"<<endl;
            break;
        }
    }
    
    cin.get();
    return 0;
}
