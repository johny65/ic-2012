#include<iostream>


#include <vector>
#include "Sistema.h"
using namespace std;





int main (int argc, char *argv[]) {

	double a[20]={0.0, 7.2, 3.6, 10.8, 7.2, 14.4, 10.8, 18.0,14.4,21.6,18.0,25.2,21.6,28.8,25.2,32.4,28.8,36.0,32.4,39.6};
	vector<double> T (a,a+sizeof(a)/sizeof(double));

	double b[20]={0.0, 44.0, 22.0, 66.0, 44.0, 88.0, 66.0, 100.0, 88.0, 132.0, 110.0, 154.0, 132.0, 176.0, 154.0, 198.0,176.0,220.0,198.0,246.0};
	vector<double> I (b,b+sizeof(b)/sizeof(double));
	
	double c[20]={0.0, 7.2, 3.6, 10.8, 7.2, 14.4, 10.8, 18.0,14.4,21.6,18.0,25.2,21.6,28.8,25.2,32.4,28.8,36.0,32.4,39.6};
	vector<double> V (c,c+sizeof(c)/sizeof(double));
	
	Sistema Temp(T,I,V);
	Temp.Simular_sincontrol();
	Temp.Simular_concontrol();
	

	
	return 0;
}

