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
	//capas ocultas
	int t = perceptrones_por_capa.size() - 1;
	for (int i=0; i<t; ++i){
		Layer nueva(perceptrones_por_capa[i]);
		this->capas.push_back(nueva);
	}

	//capa de salida (pongo a los perceptrones como hidden = false)
	Layer nueva(perceptrones_por_capa[t], false);
	this->capas.push_back(nueva);
	cout<<"red lista\n";
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
			this->capas[i][j].inicializar_pesos(capas[i-1].size() + 1);
		}
	}
	
}

Network::~Network() {
	
}


vector< vector<double> > Network::mapear(vector<double> &x){
	/**
		@param x vector de salidas deseadas escalares.
	*/

	int c = this->capas.back().size(); //si la función es de la clase no hace falta pasar esto como parámetro
	cout<<"neuronas de salidas: "<<c<<endl;

	vector< vector<double> > sal_m;
	if(c==1){
		//si hay una sola neurona en la última capa, las salidas no tiene mapeo
		//(-1 ó 1), solamente se pone cada valor en un vector aparte
		for (size_t i=0; i<x.size(); ++i) {
			sal_m.push_back(vector<double>(1, x[i]));
		}
	}
	else {
		//sino se hace el mapeo doble->vector, donde queda en +1 el elemento
		//correspondiente al valor
		vector<double> n(c, -1.0);
		for (size_t i=0; i<x.size(); ++i) {
			sal_m.push_back(n);
			sal_m[i].at(x[i]) = 1.0; //pongo el at para que tire error si tenemos menos neuronas que las que necesita el mapeo
		}
	}

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


void Network::entrenar (const char * name) {
	/** 
		@brief entrena la red neuronal
		@param name nombre del archivo que contiene los datos
	*/

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
	q = datos.begin();
	while (q != datos.end()){ //recorro todo el set de datos
		///\todo hacer que lo recorra de forma aleatoria, no secuencial

		vector<double> *entradas = &(*q); //un patrón de entrada (no todas)
		
		//paso hacia adelante:
		for (size_t k=0; k<this->capas.size(); ++k){
			Layer &capa = this->capas[k];
			vector<double> salida_capa(capa.size());
			//meter las entradas por los perceptrones de la capa
			for (size_t j=0; j<capa.size(); ++j){
				salida_capa[j] = capa[j].clasificar(*entradas); ///<\todo ver bien qué está mal, el dot del clasificar tira "diferente dimensiones"
			}
			
			entradas = &salida_capa;
			
		}
		vector<double> &salidas = *entradas; //salida de la última capa (salida de la red)
		
		
		//hacia atras:
		
		vector<double> d = dif(salidas, this->salidas_deseadas[i]);
		//double error=energia(d)/2.0;
		//error: en la capa de salida

		i++;
	}
	
//
//	
//	for (size_t i=this->capas.size(); i>=0; --i){
//		Layer &capa = this->capas[i];
//		
//	}
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
	for (int k=0; k<clases.size()-1;k++){
		sp<<"\"clase "<<clases[k]<<".dat\" lt "<<clases[k]+1<<", ";
	}
	//Este hay q separarlo porque no tiene que incluir la ',' al final
	sp<<" \"clase "<<clases[clases.size()-1]<<".dat\" lt "<<clases[clases.size()-1]+1<<" ; set title \""<<titulo<<"\"";
	plotter(sp.str());
	//wait(this->tiempo_espera);
}

