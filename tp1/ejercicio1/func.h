#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

/**
	func.h maneja todas las funciones matemáticas utilizadas por la clase Perceptron
*/

vector<double> init_weight(int nd);
vector<double> sum(vector<double> y,vector<double> x);
vector<double> dif(vector<double> y,vector<double> x);
vector<double> prod_escalar(vector<double> x, double nu);
double dot(vector<double> &x, vector<double> &y);
vector<double> recalcular_pesos(vector<double> pv, double tasa, double s,double se,vector<double> datos);
double calc_error(vector<double> &x, vector<double> &y);
double signo(double valor, double a = 1.0);
double sigmoide(double valor, double a = 1.0);

#endif
