#include<iostream>


#include <vector>
#include "Sistema.h"
using namespace std;





int main (int argc, char *argv[]) {

	double a[18]={0.0, 7.5, 5.5, 13.0, 10.0, 17.5, 15.5, 20.5, 18.5, 24.0, 23.5, 27.0, 25.5, 28.5, 27.5, 33.5, 32.0, 40.0};
	vector<double> T (a,a+sizeof(a)/sizeof(double));
	Sistema Temp(9,T);
	Temp.Simular_sincontrol();
	
//	cin.get();
	
	return 0;
}

