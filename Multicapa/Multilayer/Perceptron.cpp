#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Perceptron.h"
#include "utils.h"
#include "func.h"
#include "wait.h"
#include "GNUplot.h"

using namespace std;

/**
 * @brief Constructor por defecto.
 *
 * Por defecto el perceptrón es establecido como perteneciente a una capa
 * oculta.
 */
Perceptron::Perceptron() : hidden(true)
{
	srand(time(NULL));
}


/**
 * @brief Constructor con parámetro para establecer si es oculta o no.
 *
 * @param h true si el perceptrón está en una capa oculta, false en caso
 * contrario.
 */
Perceptron::Perceptron(bool h)
{
	this->hidden = h;
	srand(time(NULL));
}


/**
 * @brief Destructor.
 */
Perceptron::~Perceptron() {}


/**
 * Inicializa los pesos del perceptrón en valores aleatorios.
 *
 * @param num_entradas Cantidad de pesos (cantidad de entradas que tiene el
 * perceptrón contando el sesgo)
 */
void Perceptron::inicializar_pesos(int num_entradas)
{
	this->pesos = init_weight(num_entradas);
}


bool Perceptron::get_hidden(){
	return hidden;
}

/**
 * @brief Calcula el gradiente local de la neurona teniendo en cuenta si se
 * encuentra en la capa de salida o en una capa oculta.
 *
 * @param ds Vector con los gradientes locales (deltas) de las neuronas de la
 * capa siguiente. Si la neurona se encuentra en la capa de salida, ds incluye
 * un solo valor (ds[0]) que corresponde al error en la salida de la neurona
 * (es decir:
 *     ds[0] = e
 * donde:
 *     e = d - y
 * y donde:
 *     d = salida deseada para la neurona
 *     y = salida obtenida por la neurona).
 *
 */
void Perceptron::calcular_delta(vector<double> &ds)
{
	if(this->hidden){
		this->delta = derivada_sigmoide(this->v)*dot(ds, this->pesos);
		///\todo ESTÁ MAL, NO HAY QUE USAR THIS->PESOS
	}
	else{
		double &ej = ds[0];
		this->delta = ej*derivada_sigmoide(this->v);	
	}
}


/**
 * @brief Devuelve el gradiente local de la neurona.
 */
double Perceptron::get_delta(){
	return this->delta;
}


/**
 * @brief Define el número máximo de iteraciones para entrenar el Perceptron.
 * @param m Cantidad máxima de iteraciones.
 */
/*void Perceptron::set_iteraciones_max(int m)
{
	this->max_iter = m;
}*/


/**
 * @brief Define la tolerancia del error.
 *
 * A medida que va entrenando el perceptrón, se calcula una medida del error
 * entre su salida y las salidas deseadas. Cuando este error sea menor que esta
 * tolerancia, el entrenamiento se detiene.
 *
 * @param t Nueva tolerancia.
 */
/*
void Perceptron::set_tolerancia(double t)
{
	this->tol = t;
}
*/

/**
 * @brief Establece el tiempo de espera entre frames para la animación, es
 * decir el tiempo que hay que esperar para dibujar otra vez.
 * @param t Tiempo de espera.
 */
/*void Perceptron::set_tiempo_espera(double t)
{
	this->tiempo_espera = t;
}
*/

/**
 * @brief Establece si se deben mostrar los gráficos o no.
 * @param g true si se muestran gráficos, false si no.
 *//*
void Perceptron::set_graficos(bool g)
{
	this->graficos = g;
}
*/

/**
 * @brief Establece si se debe graficar el error por cada iteración.
 *//*
void Perceptron::set_show_error(bool g)
{
	this->show_error = g;
}
*/

/**
 * @brief Establece si se deben mostrar salidas por pantalla o no.
 * @param s true: salidas activadas, false: salidas desactivadas.
 *//*
void Perceptron::set_salidas(bool s)
{
	this->couts = s;
}
*/

/**
 * @brief Rutina con la cual el Perceptron aprende a partir de datos.
 * @param name Nombre del archivo .csv a leer, el mismo contiene los datos de
 * entrenamiento.
 * @return -1 si no pudo leer el archivo, 0 si tuvo éxito.
 *//*
int Perceptron::entrenar(const char *name)
{
	
	vector< vector<double> > datos=leer_csv(name, this->salidas_deseadas);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo"<<endl;return -1;}
	vector<double> entradas;
	
	vector< vector<double> >::iterator q=datos.begin();
	this->nd=(*q).size(); //cantidad total de entradas (sesgo incluido)
	
	//archivo para gnuplot
	crear_dat(datos, "plot.dat");
	
	//inicializo el vector de pesos aletoriamente con valores entre [-0.5 0.5]
	this->pesos = init_weight(nd);
	cout<<endl<<"Pesos nuevos"<<endl; mostrar_pesos(); cout<<endl;
	
	double err = 0.0;
	int iteraciones = 0;
	while (iteraciones < this->max_iter){
		salidas.clear();
		int i = 0;
		q=datos.begin();
		
		while(q!=datos.end()){
			
			entradas = *q;
			this->salidas.push_back(clasificar(entradas));
			
			if(this->salidas_deseadas[i] != salidas.back()){ //salida deseada != salida obtenida?
				pesos=recalcular_pesos(this->pesos, this->eta,
					this->salidas.back(), this->salidas_deseadas[i], entradas);				
			}
		
			if (this->couts)
				mostrar_pesos();
			
			if (this->graficos)
				graficar();
			
			q++; i++;
		}
		
		//calcular error por iteración:
		err = calc_error(this->salidas_deseadas, this->salidas);
		this->error_ent.push_back(err);

		iteraciones++;
				
		if (this->couts){
			cout<<"Error: "<<err<<endl;
			cout<<"Iteración "<<iteraciones<<endl;
		}
		
		if (err <= this->tol)
			break;
	}
	
	
	if (this->show_error){
		crear_dat_vector(this->error_ent, "error.dat");
		error_graf("plot \"error.dat\" with lines");
	}
	
	this->weight.push_back(pesos); //guardo los pesos 
	
	cout<<"Se terminó de entrenar el perceptrón.\n"<<"iteraciones "<<iteraciones<<" error "<<err<<endl;
	graficar(); //resultado final siempre se muestra
	
	//Muestro el resultado del entrenamiento
	if (this->couts){
		q=datos.begin();
		int g=0;
		while(q!=datos.end()){
			for (int i=0;i<(int)(*q).size();i++){
				cout<<setw(8)<<setprecision(3)<<(*q)[i];
			}
			cout<<"    |"<<setw(5)<<setprecision(3)<<salidas_deseadas[g];
			cout<<"    |"<<setw(5)<<setprecision(3)<<salidas[g]<<endl;
			g++;
			q++;
		}
	}
	
	error_ent.clear(); //borro errores
	salidas.clear(); //borro los datos de las salidas el Perceptron ya esta entrenado
	return 0;
}
*/

/**
 * @brief Rutina que a partir de los datos de prueba genera las salidas y grafica(idea falta implementar)
 * @param datos matriz de datos de prueba en este vector no existe salida esperada a diferencia de la rutina entrenar
 *//*
void Perceptron::probar(const char *name)
{
	vector< vector<double> > datos = leer_csv(name, this->salidas_deseadas);
	if(pesos.empty()) {cout<<"Primero debe entrenar el Perceptron"<<endl; return;}
	vector< vector<double> >::iterator q=datos.begin();

	double error_e = 0.0;
	int i=0;
	
	while(q!=datos.end()){
		this->salidas.push_back(clasificar(*q));
		error_e += calc_error_x_epoca(this->salidas_deseadas[i],this->salidas.back());
		q++; i++;
	}

	this->error.push_back(error_e); //guardo el error

	cout<<"Error de la prueba: "<<error_e<<endl;

}
*/

/**
 * @brief Función para mostrar por consola los pesos del perceptrón.
 */
void Perceptron::mostrar_pesos(){
	vector<double>::iterator q=this->pesos.begin();
	while(q!=pesos.end()){
		cout<<(*q)<<" , ";
		q++;
	}
	cout<<endl;
}


/**
 * @brief Fija la tasa de aprendizaje para el Perceptron.
 * @param n Tasa de aprendizaje nueva.
 *//*
void Perceptron::fijar_tasa(double n)
{
	this->eta = n;
}
*/

/**
 * @brief Rutina que permite seleccionar la función del Perceptron.
 * @param x Es 1-función signo, 2-función sigmoide, 3-funcion gaussiana (esta es la idea->no esta implementado)
 *//*
void Perceptron::sel_func(int x){

	if (x == 1)
		this->func = signo;
	else if (x == 2)
		this->func = sigmoide;
	
}
*/

/**
 * @brief Devuelve la salida que calcula el perceptrón para una entrada dada
 * con los pesos actuales.
 * 
 * @param D Vector con un patrón de entrada.
 * @return El valor de salida calculado.
 */
double Perceptron::clasificar(const vector<double> &D){
	this->v = dot(D, this->pesos);
	return sigmoide(this->v, 1.0);
}


/**
 * @brief Función para graficar.
 *
 * Esta función grafica, en el caso de entradas en 2 dimensiones, un plano y la
 * recta que van formando los pesos del perceptrón. En el caso de entradas con
 * 3 dimensiones, dibuja el plano que van formando los pesos del perceptrón.
 * Además también dibuja los puntos de las entradas.
 *
 * @param titulo Título para el gráfico.
 * 
 *//*
void Perceptron::graficar(const char *titulo)
{
	double &w0 = pesos[0];
	double &w1 = pesos[1];
	double &w2 = pesos[2];

	///\todo hacer que dibuje los puntos de cada clase de distintos colores
	///\todo hacer que el plano sea sólido
	
	if(pesos.size()==3){ //gráfico en 2 dimensiones
		///<\todo acá no hace zoom ni con el click del medio!
		stringstream ss;
		ss<<"plot [-2:2] [-2:2]"<<-1*(w1/w2)<<"*x + "<<w0/w2;
		ss<<", \"plot.dat\" lt 3; set title \""<<titulo<<"\"";
		plotter(ss.str());
		wait(this->tiempo_espera);
		//sleep(this->tiempo_espera);
	}
	
	else if (pesos.size() == 4){ //gráfico en 3 dimensiones
		//Zoom con click del medio!
		double &w3 = pesos[3];
		stringstream ss;
		ss<<"splot [-2:2] [-2:2] [-2:2]"<<-1*(w2/w3)<<"*y + "<<-1*(w1/w3)<<"*x + "<<w0/w3;
		ss<<", \"plot.dat\" lt 3; set title \""<<titulo<<"\"";
		plotter(ss.str());
		wait(this->tiempo_espera);
	}
}
*/

/**
 * @brief Función wrapper que dibuja un gráfico sin título.
 *//*
void Perceptron::graficar()
{
	graficar("");
}
*/

/**
 * @brief Validación cruzada.
 *
 * Esta rutina entrena el Perceptron con varias particiones, realiza las pruebas,
 * calcula el error de las mismas y escoge los pesos que tuvieron el menor error.
 *
 * @param ruta Ruta (carpeta y prefijo) de los archivos para realizar la
 * validación cruzada.
 *//*
void Perceptron::val_cross(const char *ruta)
{	
	stringstream name_e, name_p;
	name_e<<ruta<<"_e1.csv";
	name_p<<ruta<<"_p1.csv";
	int i=2;
	while(entrenar((name_e.str()).c_str())==0){
		//mientras encuentre archivos de entrenamiento-prueba, seguir
		probar(name_p.str().c_str());
		cout<<"Terminó partición "<<i-1<<".\n";
		name_e.str("");
		name_e<<ruta<<"_e"<<i<<".csv";
		name_p.str("");
		name_p<<ruta<<"_p"<<i<<".csv";
		i++;
	}
	
	
	//Buscar según el mínimo error y actualizar el vector de pesos
	double menor = this->error[0];
	int ind_m = 0;
	for (size_t i=1; i<this->error.size(); ++i){
		if(menor>this->error[i]){ menor=this->error[i]; ind_m=i;}
	}
	
	this->pesos = this->weight[ind_m];
	cout<<"\nPesos ganadores:\n";
	mostrar_pesos();
	graficar("Pesos ganadores");
	
	
	//promedio:
	double sum = 0.0;
	for (size_t i=0; i<this->error.size(); ++i){
		sum += this->error[i];
	}
	sum /= this->error.size();

	cout<<"Error de la validación cruzada: "<<sum<<endl;
	
}
*/
