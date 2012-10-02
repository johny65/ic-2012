#include <iostream>
#include "RBFNetwork.h"
#include "func.h"


using namespace std;

int main (int argc, char *argv[]) {
	RBFNetwork red;
	red.setear_arquitectura(2, 1);
	red.entrenar("xorvar.csv");
	red.probar("xorvar.csv");
	cin.get();
	return 0;
}
