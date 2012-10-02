#include <stdexcept>
#include "RBFNetwork.h"
#include "func.h"
#include "utils.h"

/**
 * @brief Constructor, fija los parámetros por defecto.
 */
RBFNetwork::RBFNetwork() :
	eta(0.1), max_epocas(1000), tol(0.01), couts(true)
{
	srand(time(NULL) + getpid());
}


/**
 * @brief Inicializa la arquitectura de la red con las capas y neuronas fijadas.
 *
 * @param unidades_ocultas Cantidad de neuronas en la capa oculta (neuronas con
 * las funciones de base radial).
 * @param unidades_salida Cantidad de neuronas en la capa de salida (perceptrones
 * con salida lineal).
 */
void RBFNetwork::setear_arquitectura(int unidades_ocultas, int unidades_salida)
{
	
	this->capa_oculta = vector<RBF>(unidades_ocultas);
	this->capa_salida = vector<Perceptron>(unidades_salida);
	
	//ya aloco el espacio para los vectores de salida de las capas:
	//(la capa de salida tiene como entrada la salida de la capa oculta más el sesgo)
	
	this->salidas_capas = vector< vector<double>* >(2);
	this->salidas_capas[0] = new vector<double>(this->capa_oculta.size() + 1, -1);
	this->salidas_capas[1] = new vector<double>(this->capa_salida.size());
		
}


/**
 * @brief Destructor.
 */
RBFNetwork::~RBFNetwork()
{
	for (size_t i=0; i<this->salidas_capas.size(); ++i){
		delete this->salidas_capas[i];
	}
}


/**
 * @brief Comprueba que se haya seteado una arquitectura y aborta la ejecución
 * en caso contrario.
 */
void RBFNetwork::verificar_inicializada()
{
	if (this->capa_oculta.size() == 0 && this->capa_salida.size() == 0){
		cout<<"No se configuró ninguna arquitectura para la red.\n";
		exit(-1);
	}
}


/**
 * @brief Mapea las salidas deseadas escalares a salidas vectoriales.
 *
 * Por ejemplo, si la salida deseada puede ser una de 3 clases (0, 1 ó 2), la
 * red debería tener 3 neuronas de salida donde se activará una sola de ellas
 * indicando la clase elegida en la clasificación. Por lo tanto las salidas
 * deseadas de la red quedan mapeadas de la siguiente forma:
 *
 * 0 => +1 -1 -1
 * 1 => -1 +1 -1
 * 2 => -1 -1 +1
 *
 * @param x vector de salidas deseadas escalares.
 */
vector< vector<double> > RBFNetwork::mapear(vector<double> &x)
{
	int c = this->capa_salida.size(); //si la función es de la clase no hace falta pasar esto como parámetro

	vector< vector<double> > sal_m;
	if(c==1){
		//si hay una sola neurona en la última capa, las salidas no tienen mapeo
		//(-1 ó +1), solamente se pone cada valor en un vector aparte
		for (size_t i=0; i<x.size(); ++i) {
			sal_m.push_back(vector<double>(1, x[i] == 0 ? -1 : x[i])); //al 0 lo pone como -1
		}
	}
	else {
		//sino, se hace el mapeo doble->vector, donde queda en +1 el elemento
		//correspondiente al valor
		vector<double> n(c, -1.0);
		for (size_t i=0; i<x.size(); ++i) {
			sal_m.push_back(n);
			try {
				sal_m[i].at(x[i]) = 1.0; //pongo el at para que tire error si tenemos menos neuronas que las que necesita el mapeo
			} catch (out_of_range ex) {
				cout<<"Error: no se pueden mapear las salidas con la cantidad \
de neuronas establecidas para la capa de salida ("<<ex.what()<<")\n";
				exit(-1);
			}
		}
	}

	//descomentar para ver cómo quedó el mapeo:
	/*
	for (int i=0; i<sal_m.size(); ++i){
		cout<<"salida: "<<x[i]<<" mapeo: ";
		for (int j=0; j<sal_m[i].size(); ++j){
			cout<<sal_m[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	
	return sal_m;
	
}


/**
 * @brief Entrena la red neuronal.
 * @param name Nombre del archivo que contiene los datos.
 */
void RBFNetwork::entrenar(const char *name)
{
	verificar_inicializada();
	
	//Abro el archivo de datos;
	vector<double> salidas_escalares;
	this->datos = leer_csv(name, salidas_escalares);

	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo."<<endl; return;}

	//mapeo las salidas deseadas a las neuronas de salida
	this->salidas_deseadas = mapear(salidas_escalares);

	if (this->couts)
		dibujar_red();


	/* Etapa 1: "entreno" las medias de las gaussianas mediante k-means */

	vector<Punto> medias = k_means(this->datos, this->capa_oculta.size());
	for (size_t i=0; i<this->capa_oculta.size(); ++i){
		this->capa_oculta[i].set_centro(medias[i]);
	}
	///\todo ver lo de entrenar los sigmas


	/* Etapa 2: entreno los pesos de los perceptrones en la capa de salida */


	//inicializo los pesos de los perceptrones
	for (size_t i=0; i<this->capa_salida.size(); ++i){
		this->capa_salida[i].inicializar_pesos(this->salidas_capas[0]->size());
	}

	//vector con índices para aleatorizar entradas
	int cant_patrones_entrada = datos.size();
	vector<int> indices(cant_patrones_entrada);
	for (size_t i=0; i<indices.size(); ++i){
		indices[i] = i;
	}
	
	//empiezo el entrenamiento
	int epocas = 0;
	vector<double> error_ent;
	vector<double> e(this->capa_salida.size()); //errores de salida (salida_obtenida - salida_deseada)
	while (epocas < this->max_epocas){ //Epoca=conjunto de datos entero es decir el archivo completo
	
		double error = 0.0; //E_av, error promedio para un set completo
		
		for (int i=0; i<cant_patrones_entrada; ++i){ //recorro todo el set de datos

			vector<double> *entradas = &datos[indices[i]]; //un patrón de entrada (no todas)

			//pasada por la capa oculta
			for (size_t j=0; j<this->capa_oculta.size(); ++j){
				RBF &neurona = this->capa_oculta[j];
				this->salidas_capas[0]->at(j+1) = neurona.clasificar(*entradas); //el +1 por el sesgo
			}

			//pasada por la capa de salida
			entradas = this->salidas_capas[0];
			for (size_t j=0; j<this->capa_salida.size(); ++j){
				Perceptron &neurona = this->capa_salida[j];
				double s = neurona.clasificar(*entradas);
				this->salidas_capas[1]->at(j) = s;
				e[j] = s - this->salidas_deseadas[indices[i]][j];
				neurona.actualizar_pesos(*entradas, e[j], this->eta);
			}

			
			double E = energia(e)/2.0; //E(n), suma del error cuadrático instantáneo
			error += E;
			
		} //termina un patrón de entrada, seguir con el siguiente

		epocas++; //cout<<"Época: "<<epocas<<endl;
		error /= datos.size();
		if (this->couts)
			cout<<"E: "<<error<<endl;
		error_ent.push_back(error);
		if (error < this->tol){
			cout<<"Terminó el entrenamiento en "<<epocas<<" épocas.\n";
			break;
		}

		//aleatorizar la presentación de patrones en la siguiente época
		random_shuffle(indices.begin(), indices.end());
		
	} //termina una época, seguir con otra

	//muestra el gráfico del error
	crear_dat_vector(error_ent, "error.dat");
	error_graf("plot \"error.dat\" with lines");
	
}

	
/**
 * @brief Validación cruzada.
 *
 * Validación de la red usando leave-k-out.
 *
 * @param archivo Archivo con el set completo de datos.
 * @param k Deja k patrones para prueba.
 *//*
void RBFNetwork::val_cross (const char * archivo, int k)
{
	if (!this->cant_capas()){
		cout<<"No se configuró ninguna arquitectura para la red.\n";
		exit(-1);
	}
	
	vector< vector<double> > datos_val = leer_csv(archivo);
	if (datos_val.size() % k != 0){
		cout<<"Error, ingrese otro k.\n";
		exit(-1);
	}

	//dibujar la red
	this->datos.push_back(datos_val[0]);
	dibujar_red();

	this->couts = false;
	int cant = datos_val.size()/k;
	vector<double> aciertos;

	int ki = 0;
	for (int i=0; i<cant; ++i){
		vector< vector<double> > kp(datos_val.begin()+ki, datos_val.begin()+ki+k);
		vector< vector<double> > ke(datos_val.begin(), datos_val.begin()+ki);
		ke.insert(ke.end(), datos_val.begin()+ki+k, datos_val.end());
		
		guardar_csv("prueba_k.csv", kp);
		guardar_csv("entrenamiento_k.csv", ke);

		this->datos.clear();
		entrenar("entrenamiento_k.csv");
		
		double porc = probar("prueba_k.csv");
		aciertos.push_back(porc);
		
		ki += k;
	}

	vector<double>::iterator m = max_element(aciertos.begin(), aciertos.end());

	double error_clas = 0.0; //promedio de error de clasificación
	vector<double> desaciertos(aciertos.size());
	for (size_t i=0; i<aciertos.size(); ++i){
		desaciertos[i] = 100 - aciertos[i];
		error_clas += desaciertos[i];
	}
	error_clas /= desaciertos.size();

	vector<double> eee = dif(desaciertos, vector<double>(desaciertos.size(), error_clas));
	double desvio = sqrt(energia(eee) / (desaciertos.size()-1));

	cout<<"\nPromedio de error (%): "<<error_clas<<endl;
	cout<<"Desvío estándar: "<<desvio<<endl;
	cout<<"Mayor porcentaje de acierto logrado: "<<*m<<endl;

	crear_dat_vector(aciertos, "aciertos.dat");
	plotter("plot \"aciertos.dat\" with boxes");
	
}
*/


double RBFNetwork::probar (const char *name) {
	vector<vector<double> > vec_dif;
	
	//Abro el archivo de datos;
	vector<double> salidas_escalares;
	this->datos.clear();
	this->datos = leer_csv(name, salidas_escalares);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo de prueba."<<endl; return -1;}
	
	//mapeo las salidas deseadas a las neuronas de salida
	this->salidas_deseadas = mapear(salidas_escalares);
	
	int aciertos=0;//para contar la cantidad de aciertos
	
	vector<vector<double> > result_c; //resultado de la clasificacion de los datos vector<vector<>> xq tengo un vector de salida por cada dato (por el mapear)

	vector<int> salidas_mias_lindas;
	
	for(size_t i=0;i<this->datos.size();i++) {  
		//cout<<"dimension de datos "<<datos[i][0]<<"   "<<datos[i][1]<<"   "<<datos[i][2]<<endl;
		result_c.push_back(clasificar(this->datos[i])); //guardo el resultado de la clasificacion de cada dato
		vec_dif.push_back(dif(this->salidas_deseadas[i],result_c.back()));
		if(this->salidas_deseadas.back().size()==1){//si pasa por aca quiere decir que las salidas son solo 1 o -1 (no hay mapeo a vector)
			//if(abs(vec_dif[i][0])<0.07){
			if (signo(result_c[i][0]) == this->salidas_deseadas[i][0]){
				aciertos++;
			}
			this->datos[i].push_back(signo(result_c[i][0]));
		}
		else{//tengo que ver que neurona se activo busco el maximo valor
			vector<double>::iterator m = max_element(result_c[i].begin(), result_c[i].end());
			int ind = distance(result_c[i].begin(), m);
			if (this->salidas_deseadas[i][ind] == 1)
				aciertos++;
			this->datos[i].push_back(ind); //agrego mi salida para ya dibujar
		}
	}
	
	cout<<"Número de aciertos: "<<aciertos<<"/"<<this->datos.size()<<endl;
	double porc = aciertos*100.0/this->datos.size();
	cout<<"% de aciertos: "<<porc<<"%"<<endl;
	
	//generar un archivo .txt para graficar los puntos con la clasificacion obtenida
	if (this->couts){
		guardar_csv("resultados.csv", this->datos);
		graficar_puntos("resultados.csv", "resultados");
	}
	
	return porc;
}



void RBFNetwork::graficar_puntos(const char *archivo, const char *titulo)
{
	vector< vector<double> > datos;
	vector<double> salidas;
	vector<double> clases;
	
	std::ostringstream sp;
	datos=leer_csv(archivo, salidas);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo"<<endl;return;}
	int j=0;
	vector< vector<double> >::iterator q=datos.begin();
	
	//archivo para gnuplot		
	while(q!=datos.end()){
		std::ostringstream ss;
		char nombre[15];
		sprintf(nombre, "clase %d.dat",  (int)salidas[j]);
		ofstream out(nombre, ios::app);
		int n=(*q).size();
		for(int i=0;i<n;++i){
			if(i!=n-1) ss << ((*q)[i]) << " ";
			else ss << ((*q)[i]) << endl;
		}
		out<<ss.str();
		out.close();
		//Cargamos la clase en el vector de clases
		if (find(clases.begin(), clases.end(), salidas[j])==clases.end()){
			clases.push_back(salidas[j]);
		}
		q++;
		j++;
	}
	
	//Para que GNUPLOT Grafique todas las clases
	sp<<"plot ";
	for (size_t k=0; k<clases.size()-1;k++){
		sp<<"\"clase "<<clases[k]<<".dat\" lt "<<k+1<<", ";
	}
	//Este hay q separarlo porque no tiene que incluir la ',' al final
	sp<<" \"clase "<<clases[clases.size()-1]<<".dat\" lt "<<clases.size()<<" ; set title \""<<titulo<<"\"";
	plotter(sp.str());
	//wait(this->tiempo_espera);

	//Borramos los archivos creados para dibujar
	for( int j=0;j<100000000;j++){}
	for (size_t k=0; k<clases.size();k++){
		char nomb[15];
		sprintf(nomb, "clase %d.dat",(int)clases[k]);
		remove(nomb);
	}
	
}


/**
 * @brief Define el número máximo de épocas (iteraciones) para entrenar la
 * red.
 * @param m Cantidad máxima de épocas (presentación completa de todos los patrones
 * de entrada).
 */
void RBFNetwork::set_max_epocas(int m)
{
	this->max_epocas = m;
}


/**
 * @brief Fija la tasa de aprendizaje de la red.
 * @param n Tasa de aprendizaje nueva.
 */
void RBFNetwork::set_tasa(double n)
{
	this->eta = n;
}


/**
 * @brief Define la tolerancia del error.
 *
 * A medida que va entrenando la red, se calcula una medida del error
 * entre su salida y las salidas deseadas. Cuando este error sea menor que esta
 * tolerancia, el entrenamiento se detiene.
 *
 * @param t Nueva tolerancia.
 */
void RBFNetwork::set_tolerancia(double t)
{
	this->tol = t;
}


/**
 * @brief Mete un dato de entrada en la red y obtiene la respuesta de salida.
 * @param Datos Entrada a evaluar.
 */
vector<double> RBFNetwork::clasificar(vector<double> &Datos)
{
	//primero lo paso por la capa oculta
	for (size_t i=0; i<this->capa_oculta.size(); ++i){
		RBF &neurona = this->capa_oculta[i];
		this->salidas_capas[0]->at(i+1) = neurona.clasificar(Datos); //el +1 por el sesgo
	}

	//después lo paso por la capa de salida
	vector<double> &entradas = *this->salidas_capas[0];
	for (size_t i=0; i<this->capa_salida.size(); ++i){
		Perceptron &neurona = this->capa_salida[i];
		this->salidas_capas[1]->at(i) = neurona.clasificar(entradas);
	}

	vector<double> *salidas = this->salidas_capas[1];
	return *salidas;
}


/**
 * @brief Función para dibujar la estructura de la red neuronal.
 *
 * Hace un grafiquito mostrando cómo es la estructura de la red según se
 * configuró. Requiere tener `graphviz` instalado (el programa `dot`) e
 * `ImageMagick` para mostrar la imagen (el programa `display`).
 */
void RBFNetwork::dibujar_red()
{
	///\todo tratar de ponerle dibujitos a las neuronas
	
	ofstream f("red.gv");
	f<<"digraph {\nrankdir=LR\n";
	for (size_t i=0; i<this->datos[0].size(); ++i){
		f<<"x"<<i<<" [shape=point, label=\"\"]\n";
	}
	for (size_t i=0; i<this->capa_oculta.size(); ++i){
		f<<"c1p"<<i<<" [shape=circle, label=\"\"]\n";
	}
	for (size_t i=0; i<this->capa_salida.size(); ++i){
		f<<"c2p"<<i<<" [shape=circle, label=\"\"]\n";
		f<<"s"<<i<<" [style=invisible, shape=point, label=\"\"]\n";
	}

	for (size_t i=0; i<this->datos[0].size(); ++i){
		for (size_t j=0; j<this->capa_oculta.size(); ++j){
			f<<"x"<<i<<" -> c1p"<<j<<endl;
		}
	}
	
	for (size_t i=0; i<this->capa_oculta.size(); ++i){
		for (size_t j=0; j<this->capa_salida.size(); ++j){
			f<<"c1p"<<i<<" -> c2p"<<j<<endl;
		}
	}
	
	for (size_t i=0; i<this->capa_salida.size(); ++i){
		f<<"c2p"<<i<<" -> s"<<i<<endl;
	}
	
	f<<"\n}";
	f.close();
	system("dot -Tpng -ored.png red.gv");
	//system("display red.png");
	if (fork() == 0){ //de esta forma no espera a que el programa termine
		execlp("display", "display", "red.png", NULL);
		exit(1);
	}
}


/**
 * @brief Función para guardar los pesos de la red en un Archivo.
 *//*
void RBFNetwork::guardar_pesos(){
	for (size_t i=0; i<this->capas.size(); ++i){
		vector< vector<double> > pesos_capa;
		for (size_t j=0; j<capas[i].size(); ++j){
			pesos_capa.push_back(capas[i][j].get_vector_pesos());
		}
		pesos_a_archivo(pesos_capa);
	}
}
*/
