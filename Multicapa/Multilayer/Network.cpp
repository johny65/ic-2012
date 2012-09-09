#include "Network.h"

Network::Network(int cant_capas, vector<double> perceptrones_por_capa) {
	
	for (int i=0; i<cant_capas; ++i){
		Layer nueva(perceptrones_por_capa[i]);
		this->capas.push_back(nueva);
	}
	
}

void Network::inicializar_pesos()
{
	for (int j=0; j<this->capas[0].size(); ++j){
		this->capas[0][j].inicializar_pesos(this->datos[0].size());
	}
	
	for (int i=1; i<this->capas.size(); ++i){
		for (int j=0; j<this->capas[i].size(); ++j){
			this->capas[i][j].inicializar_pesos(capas[i-1].size());
		}
	}
}

Network::~Network() {
	
}

void Network::entrenar (const char * name) {
	/** 
		@brief entrena la red neuronal
		@param name nombre del archivo que contiene los datos
	*/
	///< 1- Abro el archivo de datos;
	this->datos = leer_csv(name, this->salidas_deseadas);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo"<<endl;return;}
	inicializar_pesos();
	
	vector<double> &entradas = this->datos[0];
	
	//paso hacia adelante:
	
	for (size_t i=0; i<this->capas.size(); ++i){
		Layer &capa = this->capas[i];
		vector<double> salida_capa(capa.size());
		//meter las entradas por los perceptrones de la capa
		for (size_t j=0; j<capa.size(); ++j){
			salida_capa[j] = capa[j].clasificar(entradas);
		}
		
		entradas = salida_capa;
		
	}
	vector<double> salidas = entradas;
	
	//hacia atras:
	
//	for (size_t i=this->capas.size(); i>=0; --i){
//		Layer &capa = this->capas[i];
//		
//	}
	
	
	//vector<double> salidas = entradas;
	for (size_t i=0; i<salidas.size(); ++i)
		cout<<salidas[i]<<" ";
	cout<<endl;
	
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
