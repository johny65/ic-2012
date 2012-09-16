#include<iostream>

#include "Network.h"
using namespace std;

int main (int argc, char *argv[]) {

	Network NN;
	
	char *archivo_entrada = NULL;
	char *archivo_prueba = NULL;
	//char *ruta_cross_val = NULL;

	string ayudassss = "\
Perceptrón Multicapa. IC 2012\n\
Opciones:\n\
 -e archivo:\n\tArchivo de entrada para datos de entrenamiento.\n\
 -p archivo:\n\tArchivo de entradas para las pruebas.\n\
 -n tasa:\n\tTasa de aprendizaje.\n\
 -m alfa:\n\tConstante para el término de momento.\n\
 -t tol:\n\tTolerancia de error para detener entrenamiento.\n\
 -i cant:\n\tNúmero máximo de iteraciones para el entrenamiento.\n\
 -w ms:\n\tTiempo entre cuadros de la animación.\n\
 -g:\n\tNo mostrar ningún gráfico.\n\
 -s:\n\tNo mostrar ninguna salida por consola.\n\
 -z:\n\tMostrar gráfico de error.\n\
 -v ruta+prefijo:\n\tRealiza validación cruzada.\n\
 -h:\n\tMuestra este mensaje de ayuda.\n\
";

	string ayuda = "\
Perceptrón Multicapa. IC 2012\n\
Uso:\n\
\tmulticapa [opciones] p1 p2 ... pn\n\n\
donde p1 es la cantidad de neuronas en la capa 1, p2 es la cantidad de neuronas\
 en la capa 2, y pn es la cantidad de neuronas en la capa n.\n\
Opciones:\n\
 -e archivo:\n\tArchivo de entrada para datos de entrenamiento.\n\
 -p archivo:\n\tArchivo de entradas para las pruebas.\n\
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
	
	int o;
	while ((o = getopt(argc, argv, "e:p:n:t:i:m:gszh")) != -1){
		switch (o){
			case 'e': {
				archivo_entrada = optarg;
				break;
			}
			case 'p': {
				archivo_prueba = optarg;
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

	if (archivo_entrada != NULL)
		NN.entrenar(archivo_entrada);
	if (archivo_prueba != NULL)
		NN.probar(archivo_prueba);
	//if (ruta_cross_val != NULL)
		//P.val_cross(ruta_cross_val);

	cout<<"\nPresionar una tecla para cerrar.\n"; cin.get();
	return 0;
	
/*
	
	vector<double> p;
	//p.push_back(4);
	p.push_back(2);
	p.push_back(10);
	//p.push_back(10);
	p.push_back(1);
	Network A(p);
	//cout<<A.cant_capas()<<endl;
	//A.entrenar("tabla_XOR.csv");
	A.entrenar("xorvar.csv");
	//A.entrenar("test.csv");
	//A.entrenar("concent.csv");
	//A.mostrar_pesos();
	//pruebo con un dato 
	vector<double> x,s;
	x.push_back(1); 	x.push_back(-1);
	s=A.clasificar(x);
	cout<<"Resultado "<<endl;
	for(size_t i=0;i<s.size();i++) { cout<<s[i]<<endl; }
	//cin.get();
	return 0;
	*/
}
