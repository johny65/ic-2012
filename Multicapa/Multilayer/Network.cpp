#include <stdexcept>
#include "Network.h"
#include "func.h"

/**
 * @brief Constructor.
 * Inicializa la arquitectura de la red con las capas y neuronas fijadas.
 *
 * @param perceptrones_por_capa Vector donde cada elemento indica la cantidad
 * de perceptrones que va a haber en esa capa (la cantidad de capas la establece
 * la longitud del vector).
 */
Network::Network(vector<double> perceptrones_por_capa)
{
	//capas ocultas (la capa de entrada es considerada capa oculta)
	int t = perceptrones_por_capa.size() - 1;
	for (int i=0; i<t; ++i){
		Layer nueva(perceptrones_por_capa[i], true);
		this->capas.push_back(nueva);
	}

	//capa de salida (pongo a los perceptrones como hidden = false)
	Layer nueva(perceptrones_por_capa[t], false);
	this->capas.push_back(nueva);

	//ya aloco el espacio para los vectores de salida de las capas;
	
	this->salidas_capas = vector< vector<double>* >(cant_capas());
	for (int i=0; i<cant_capas()-1; ++i){
		//si la capa es oculta, su salida será la entrada para otra capa,
		//entonces hay que agregar el -1 del sesgo
		this->salidas_capas[i] = new vector<double>(this->capas[i].size() + 1, -1);
	}
	//a la capa de salida no
	this->salidas_capas.back() = new vector<double>(this->capas.back().size());
	
}


/**
 * @brief Devuelve la cantidad de capas de la red.
 */
int Network::cant_capas()
{
	return this->capas.size();
}


/**
 * @brief Para inicializar todos los pesos de la red (los pesos de todas las
 * neuronas que tiene).
 */
void Network::inicializar_pesos()
{
	//recorro todos los perceptrones diciéndoles que inicializen sus pesos

	//para los que están en la capa de entrada, la cantidad de pesos que tienen
	//es igual al número de entradas)
	for (size_t j=0; j<this->capas[0].size(); ++j){
		this->capas[0][j].inicializar_pesos(this->datos[0].size());
	}

	//para los demás la cantidad de pesos es igual a la cantidad de perceptrones
	//en la capa anterior más el peso correspondiente al sesgo
	for (size_t i=1; i<this->capas.size(); ++i){
		for (size_t j=0; j<this->capas[i].size(); ++j){
			this->capas[i][j].inicializar_pesos(capas[i-1].size()+1);
		}
	}
	
}


/**
 * @brief Destructor.
 */
Network::~Network() {}


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
vector< vector<double> > Network::mapear(vector<double> &x)
{

	///\todo ver bien lo de los valores de salida deseadas (deberían estar en el rango de la sigmoide)
	///\todo ver eso del epsilon
	
	int c = this->capas.back().size(); //si la función es de la clase no hace falta pasar esto como parámetro

	vector< vector<double> > sal_m;
	if(c==1){
		//si hay una sola neurona en la última capa, las salidas no tienen mapeo
		//(-1 ó +1), solamente se pone cada valor en un vector aparte
		for (size_t i=0; i<x.size(); ++i) {
			sal_m.push_back(vector<double>(1, x[i]));
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
 * @brief Devuelve si una capa es oculta o no.
 * @param x Capa a evaluar.
 */
bool Network::is_hidden(Layer x){
	return x[0].get_hidden();
}


/**
 * @brief Entrena la red neuronal.
 * @param name Nombre del archivo que contiene los datos.
 */
void Network::entrenar(const char * name) {

	//Abro el archivo de datos;
	vector<double> salidas_escalares;
	this->datos = leer_csv(name, salidas_escalares);
	
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo."<<endl; return;}

	//mapeo las salidas deseadas a las neuronas de salida
	this->salidas_deseadas = mapear(salidas_escalares);

	//inicializo los pesos de la red
	inicializar_pesos();
	
	
	vector< vector<double> >::iterator q;
	//int epocas = 0;
	///\todo hacer todo lo siguiente para muchas épocas
	int i = 0;
	int ic; //índice de capa para llenar el vector de salida de cada capa
	q = datos.begin(); cout<<"Cantidad de patrones: "<<datos.size()<<endl;
	while (q != datos.end()){ //recorro todo el set de datos
		///\todo hacer que lo recorra de forma aleatoria, no secuencial

		vector<double> *entradas = &(*q); //un patrón de entrada (no todas)
		

		/*----------- paso hacia adelante: --------------*/
		
		for (size_t k=0; k<this->capas.size(); ++k){
			
			Layer &capa = this->capas[k]; //parado en la capa k
			if (is_hidden(capa))
				ic = 1; //empezar a llenar salida_capa desde el índice 1 (el 0 es el -1 del sesgo)
			else
				ic = 0; //empezar a llenar salida_capa desde el índice 0

			//cout<<"Capa "<<k+1<<" - Tamano de la entrada: "<<entradas->size()<<endl;

			//meter las entradas por los perceptrones de la capa
			vector<double> *salida_capa = this->salidas_capas[k];
			for (size_t j = ic; j<capa.size(); ++j){ //for por cada neurona de la capa k
				salida_capa->at(j) = capa[j-ic].clasificar(*entradas);
			}
			
			//cout<<"Tamaño salida: "<<salida_capa->size()<<endl;

			entradas = salida_capa;
			
		} //termina forward para el primer dato del archivo
		
		vector<double> &salidas = *entradas; //salida de la última capa (salida de la red)

		

		/*------------- paso hacia atrás: --------------*/
		
		vector<double> e = dif(salidas, this->salidas_deseadas.at(i)); //errores en la salida de cada neurona

		/* primero última capa:
		 * me paro en la última capa y recorro las neuronas calculando el gradiente
		 * local en cada una con el error en sus salidas (e)
		 */
		Layer &ultima_capa = this->capas.back();
		for (size_t j=0; j<ultima_capa.size(); ++j){
			ultima_capa[j].calcular_delta(e[j]);
		}

		/* ahora las otras:
		 * recorro las demás capas; me paro en la capa k y recorro sus neuronas
		 * calculando el gradiente local en cada una mediante los calculados en
		 * la capa k+1
		 */
		for (int k = this->capas.size()-2; k>=0; --k){
			
			Layer &capa = this->capas[k];
			Layer &capa_posterior = this->capas[k+1];
			
			for (size_t j=0; j<capa.size(); ++j){
				capa[j].calcular_delta(capa_posterior, j);
			}

			/* actualizar pesos de la capa k+1:
			 * una vez calculados los gradientes locales en la capa k, puedo
			 * actualizar los pesos en la capa k+1
			 */
			for (size_t j=0; j<capa_posterior.size(); ++j){
				capa_posterior[j].actualizar_pesos(*this->salidas_capas[k], this->eta);
			}

		}

		//en este punto me falta actualizar los pesos de la primera capa
		for (size_t j=0; j<this->capas.front().size(); ++j){
			this->capas.front()[j].actualizar_pesos(*q, this->eta);
		}
		
		
		//double error=energia(e)/2.0;
		//error: en la capa de salida
		//break;
		q++;
		i++;
	}
	
//
//	

//	
	
//	vector<double> salidas = entradas;
//	for (size_t i=0; i<salidas.size(); ++i)
//		cout<<salidas[i]<<" ";
//	cout<<endl;
	
}



void Network::val_cross (const char * ruta) {
	
}

void Network::probar (const char * name) {
	
}

void Network::graficar_puntos(const char *archivo, const char *titulo)
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
		for(int i=1;i<n;++i){
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
		sp<<"\"clase "<<clases[k]<<".dat\" lt "<<clases[k]+1<<", ";
	}
	//Este hay q separarlo porque no tiene que incluir la ',' al final
	sp<<" \"clase "<<clases[clases.size()-1]<<".dat\" lt "<<clases[clases.size()-1]+1<<" ; set title \""<<titulo<<"\"";
	plotter(sp.str());
	//wait(this->tiempo_espera);
}

