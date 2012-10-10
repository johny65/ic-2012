#include<iostream>


#include <vector>
#include "Sistema.h"
using namespace std;





int main (int argc, char *argv[]) {

	double a[10]={-10.0, 10.0, 6.0, 18.0, 15.0, 26.0, 18.0, 28.0, 25.0, 52.0};
	vector<double> T (a,a+sizeof(a)/sizeof(double));
	Sistema Temp(5,T,T,T);
	Temp.Simular_sincontrol();
	Temp.Simular_concontrol();

	
//	cin.get();
	
	return 0;
}

