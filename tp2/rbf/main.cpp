#include <iostream>
#include "RBFNetwork.h"
#include "func.h"


using namespace std;

int main (int argc, char *argv[]) {
/*
	Network NN;
	
	char *archivo_entrada = NULL;
	char *archivo_prueba = NULL;
	char *archivo_val = NULL;

	string ayuda = "\
Perceptrón Multicapa. IC 2012\n\
Uso:\n\
\tmulticapa [opciones] p1 p2 ... pn\n\n\
donde p1 es la cantidad de neuronas en la capa 1, p2 es la cantidad de neuronas\
 en la capa 2, y pn es la cantidad de neuronas en la capa n.\n\
Opciones:\n\
 -e archivo:\n\tArchivo de entrada para datos de entrenamiento.\n\
 -p archivo:\n\tArchivo de entradas para las pruebas.\n\
 -v archivo\n\tArchivo para realizar la validación cruzada.\n\
 -k valor\n\tK para el leave-k-out.\n\
 -n tasa:\n\tTasa de aprendizaje.\n\
 -t tol:\n\tTolerancia de error para detener entrenamiento.\n\
 -m alfa:\n\tConstante para el término de momento.\n\
 -a valor:\n\tConstante a para la sigmoidea.\n\
 -i cant:\n\tNúmero máximo de iteraciones (épocas) para el entrenamiento.\n\
 -g:\n\tNo mostrar ningún gráfico.\n\
 -s:\n\tNo mostrar ninguna salida por consola.\n\
 -z:\n\tMostrar gráfico de error.\n\
 -h:\n\tMuestra este mensaje de ayuda.\n\
";
	
	int o, k = 1;
	while ((o = getopt(argc, argv, "e:p:n:t:i:v:k:m:gszh")) != -1){
		switch (o){
			case 'e': {
				archivo_entrada = optarg;
				break;
			}
			case 'p': {
				archivo_prueba = optarg;
				break;
			}
			case 'v': {
				archivo_val = optarg;
				break;
			}
			case 'k': {
				stringstream ss; ss<<optarg; ss>>k;
				break;
			}
			//case 'z': {
				//P.set_show_error(true);
				//break;
			//}
			case 'n': {
				double tasa;
				stringstream ss; ss<<optarg; ss>>tasa;
				NN.set_tasa(tasa);
				break;
			}
			case 't': {
				double tol;
				stringstream ss; ss<<optarg; ss>>tol;
				NN.set_tolerancia(tol);
				break;
			}
			case 'i': {
				int it;
				stringstream ss; ss<<optarg; ss>>it;
				NN.set_max_epocas(it);
				break;
			}
			case 'm': {
				double alfa;
				stringstream ss; ss<<optarg; ss>>alfa;
				NN.set_momento(alfa);
				break;
			}
			//case 'a': {
				//double a;
				//ss<<optarg; ss>>a;
				//NN.set_momento(alfa);
				//break;
			//}
			//case 'g': {
				//P.set_graficos(false);
				//break;
			//}
			//case 's': {
				//P.set_salidas(false);
				//break;
			//}
			case 'h':
			case '?': {
				cout<<ayuda<<endl;
				return -1;
			}
		}
	}

	//arquitectura:
	vector<int> red;
	for (int i=optind; i<argc; ++i){
		int p;
		stringstream ss; ss<<argv[i]; ss>>p;
		red.push_back(p);
	}
	if (red.size())
		NN.setear_arquitectura(red);


	if (archivo_val != NULL)
		NN.val_cross(archivo_val, k);
		
	if (archivo_entrada != NULL){
		NN.entrenar(archivo_entrada);
		NN.guardar_pesos();
	}
	if (archivo_prueba != NULL)
		cout<<"Porcentaje de aciertos: "<<NN.probar(archivo_prueba)<<endl;



	//if (ruta_cross_val != NULL)
		//P.val_cross(ruta_cross_val);

	//NN.val_cross("xorvar.csv", 1000);
	cout<<"\nPresionar una tecla para cerrar.\n"; cin.get();
	return 0;
*/
	RBFNetwork red;
	red.setear_arquitectura(2, 1);
	red.entrenar("concent.csv");
	red.probar("concent.csv");
	cin.get();
	return 0;
}
