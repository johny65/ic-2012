#include <iostream>
#include <unistd.h>
#include "func.h"
#include "argparser.h"

int main(int argc, char **argv){

    srand(time(NULL) + getpid());
	ArgParserNew(parser);
	parser.opcion("maxiter", 'i', "Cantidad máxima de iteraciones", "100");
	parser.opcion("func", 'f', "Función a probar", "1");
    parser.opcion("eta", 'd', "Constante para el gradiente descendiente", "0.01");
    parser.opcion_bool("graf", 'g', "Graficar función");
	parser.parsear(true);
    
    //gradiente descendiente:

    int maxiter = parser.get("maxiter");
    int funcnum = parser.get("func");
    double eta = parser.get_double("eta");

    GNUplot p;
    bool graf = parser.is("graf");
    
    switch (funcnum) {
        case 1: {
            double r = rand()%1024 - 512;
            cout<<"Punto inicial: "<<r<<endl;
            vector<double> inicio(1, r);
            double x = descent(inicio, derivada1, maxiter, eta)[0];
            cout<<"GD: "<<func1(x)<<" en x = "<<x<<endl;

            if (graf)
                p("plot [-512:512] -x * sin(sqrt(abs(x)))");
            break;
        }
        case 2: {
            double r = rand()*1.0/RAND_MAX * 20;
            cout<<"Punto inicial: "<<r<<endl;
            vector<double> inicio(1, r);
            double x = descent(inicio, derivada2, maxiter, eta)[0];
            cout<<"GD: "<<func2(x)<<" en x = "<<x<<endl;

            if (graf)
                p("plot [0:20] x + 5*sin(3*x) + 8*cos(5*x)");
            break;
        }
        case 3: {
            double r1 = (rand()*1.0/RAND_MAX - 0.5) * 100;
            double r2 = (rand()*1.0/RAND_MAX - 0.5) * 100;
            cout<<"Punto inicial: ("<<r1<<", "<<r2<<")"<<endl;
            vector<double> inicio; inicio.push_back(r1); inicio.push_back(r2);
            vector<double> x = descent(inicio, derivada3, maxiter, eta);
            cout<<"GD: "<<func3(x[0], x[1])<<" en (x,y) = ("<<x[0]<<", "<<x[1]<<")"<<endl;

            if (graf){
                string s = "set isosamples 100,100\n";
                s += "set hidden3d\n";
                s += "splot [-100:100][-100:100] (x**2 + y**2)**0.25 * ( sin(50 * (x**2+y**2)**0.1)**2 + 1)\n";
                p(s);
            }
        }
    }

    cin.get();
    return 0;
}
