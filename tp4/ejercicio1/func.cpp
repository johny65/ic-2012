#include <iostream>
#include <cmath>
#include <cassert>
#include <sstream>
#include <limits>
#include "func.h"


using namespace std;

/**
 * @brief Convierte una cadena binaria a un entero.
 * @param inicio Iterador que indica el inicio de la cadena.
 * @param fin Iterador que indica el fin de la cadena.
 * @param neg Si es true, el número de salida puede ser negativo (el primer
 * bit indica el signo).
 * @return Un entero.
 */
int bin2dec(iterador inicio, iterador fin, bool neg)
{
	//cout<<distance(inicio, fin)<<endl;
    int res = 0;
    int l = distance(inicio, fin) - (neg ? 2 : 1);
    while (l >= 0){
        if (*(fin - 1 - l) == '1')
            res += pow(2, l);
        l--;
    }
    if (neg && *inicio == '1'){
		res *= -1;
	}
	return res;
}


/**
 * @brief Decodifica un cromosoma.
 * 
 * El cromosoma representa un número real. Usa A bits para la parte entera
 * y el resto de bits para la parte decimal.
 *
 * @param inicio Iterador que indica el inicio del cromosoma.
 * @param fin Iterador que indica el fin del cromosoma.
 * @param A Cantidad de bits para la parte entera.
 * @param neg Si es true, es un entero con signo, sino un entero sin signo.
 */
double decode(iterador inicio, iterador fin, int A, bool neg)
{		
    stringstream ss;
    ss<<bin2dec(inicio, inicio+A, neg);
    ss<<".";
    ss<<bin2dec(inicio+A, fin, false);

    double res;
    ss>>res;
    return res;
}


/**
 * @brief Función wrapper para poder pasar un cromosoma completo.
 */
double decode(const Cromosoma &c, int A, bool neg)
{
	return decode(c.begin(), c.end(), A, neg);
}


/**
 * @brief Función 1. Mínimo: -418.98 en x = 420.97
 */
double func1(double x)
{
    return -x * sin(sqrt(fabs(x)));
}


/**
 * @brief Decodificación para Función 1.
 *
 * 10 bits parte entera.
 */
double var1(Cromosoma &c)
{
	return decode(c, 10, true);
}


/**
 * @brief Función de fitness para la Función 1.
 *
 * Valores de x en el rango [-512,512].
 */
double fitness1(Individuo &i)
{
    double x = var1(i.cromosoma);
    return -func1(x);
}


/**
 * @brief Función 2. Mínimo: -9.4338 en x = 1.8270
 *
 * Valores de x en el rango [0,20].
 */
double func2(double x)
{
    return x + 5*sin(3*x) + 8*cos(5*x);
}


/**
 * @brief Decodificación para Función 2.
 *
 * 5 bits parte entera, limitando hasta 20.
 */
double var2(Cromosoma &c)
{
	return fmod(decode(c, 5, false), 21.0);
}


/**
 * @brief Función de fitness para la Función 2.
 */
double fitness2(Individuo &i)
{
    double x = var2(i.cromosoma);
    return -func2(x);
}


/**
 * @brief Función 3. Mínimo: 0.0 en (x,y) = 0.
 *
 * Valores de x,y en el rango [-100,100].
 */
double func3(double x, double y)
{
    double xx = x*x, yy = y*y, xy = xx + yy;
    double s = sin(50 * pow(xy, 0.1));
    return pow(xy, 0.25) * (s*s + 1);
}


/**
 * @brief Decodificación para Función 3.
 */
pair<double, double> var3(Cromosoma &c)
{
	//8 bits parte entera (7 -> 128, 8 para -128,128)
    //3 bits decimal
    //total l = 8+3+8+3 = 11+11 = 22

    double x = decode(c.begin(), c.begin()+8, 8, true);
    double y = decode(c.begin()+11, c.end(), 8, true);
    return make_pair<double, double>(x, y);
}


/**
 * @brief Función de fitness para la Función 3.
 */
double fitness3(Individuo &i)
{
    pair<double, double> val = var3(i.cromosoma);
    double x = val.first;
    double y = val.second;
    return -func3(x, y);
}



//para gradiente descendiente: -------------------------------------------


X descent(X &inicio, double (*der)(X&), int maxiter, double eta)
{
	X x(inicio);
	int it = 0;
	while (it < maxiter){
		double g = eta*der(x);
		for (size_t i=0; i<x.size(); ++i){
			x[i] -= g;
		}
		it++;
	}
	return x;
}


/**
 * @brief Derivada de la Función 1.
 */
double derivada1(X &val)
{
	double &x = val[0];
	double xx = pow(x*x, 1.0/4.0);
	return (-1.0/2.0) * xx * cos(xx) - sin(xx);
}


/**
 * @brief Derivada de la Función 2.
 */
double derivada2(X &val)
{
	double &x = val[0];
	return 1 + 15 * cos(3*x)- 40*sin(5*x);
}


/**
 * @brief Derivada de la Función 3.
 */
double derivada3(X &val)
{
	double &x = val[0];
	double &y = val[1];

	double xy = x*x + y*y;

	return (0.5 * x * (1+pow(sin(50*pow(xy, 0.1)), 2))) / pow(xy, 0.75)
		+ (10.0 * x * sin(100 * pow(xy, 0.1))) / pow(xy, 0.65);
}
