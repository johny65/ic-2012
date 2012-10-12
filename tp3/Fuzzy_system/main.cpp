#include<iostream>


#include <vector>
#include "Sistema.h"
using namespace std;





int main (int argc, char *argv[]) {

	double a[20]={0.0, 7.2, 3.6, 10.8, 7.2, 14.4, 10.8, 18.0,14.4,21.6,18.0,25.2,21.6,28.8,25.2,32.4,28.8,36.0,32.4,39.6};
	vector<double> T (a,a+sizeof(a)/sizeof(double));
	Sistema Temp(T,T,T);

	
//	cin.get();
	
	return 0;
}

