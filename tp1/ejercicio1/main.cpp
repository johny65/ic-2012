#include <iostream>
#include <sstream>
#include "Perceptron.h"

using namespace std;

int main (int argc, char *argv[]) {
	
	Perceptron P;

	char *archivo_entrada = NULL;
	char *archivo_prueba = NULL;
	char *ruta_cross_val = NULL;
	stringstream ss;

	string ayuda = "\
Perceptrón Simple. IC 2012\n\
Opciones:\n\
 -e archivo:\n\tArchivo de entrada para datos de entrenamiento.\n\
 -p archivo:\n\tArchivo de entradas para las pruebas.\n\
 -n tasa:\n\tTasa de aprendizaje.\n\
 -t tol:\n\tTolerancia de error para detener entrenamiento.\n\
 -i cant:\n\tNúmero máximo de iteraciones para el entrenamiento.\n\
 -w ms:\n\tTiempo entre cuadros de la animación.\n\
 -g:\n\tNo mostrar ningún gráfico.\n\
 -s:\n\tNo mostrar ninguna salida por consola.\n\
 -v ruta+prefijo:\n\tRealiza validación cruzada.\n\
 -h:\n\tMuestra este mensaje de ayuda.\n\
";
	
	int o;
	while ((o = getopt(argc, argv, "e:p:n:w:t:i:v:ghs")) != -1){
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
				ruta_cross_val = optarg;
				break;
			}
			case 'n': {
				double tasa;
				ss<<optarg; ss>>tasa;
				P.fijar_tasa(tasa);
				break;
			}
			case 'w': {
				double ms;
				ss<<optarg; ss>>ms;
				P.set_tiempo_espera(ms);
				break;
			}
			case 't': {
				double tol;
				ss<<optarg; ss>>tol;
				P.set_tolerancia(tol);
				break;
			}
			case 'i': {
				int it;
				ss<<optarg; ss>>it;
				P.set_iteraciones_max(it);
				break;
			}
			case 'g': {
				P.set_graficos(false);
				break;
			}
			case 's': {
				P.set_salidas(false);
				break;
			}
			case 'h':
			case '?': {
				cout<<ayuda<<endl;
				return -1;
			}
		}
	}

	P.entrenar(archivo_entrada);
	if (archivo_prueba != NULL)
		P.probar(archivo_prueba);
	if (ruta_cross_val != NULL)
		P.val_cross(ruta_cross_val);

	cout<<"\nPresionar una tecla para cerrar.\n"; cin.get();
	return 0;
}
