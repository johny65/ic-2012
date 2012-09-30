#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <limits>
#include <GL/glut.h>
#include "SOM.h"
#include "utils.h"
#include "func.h"
#include "wait.h"


/**
 * @brief Constructor.
 * Inicializa la tasa de aprendizaje en los valores recomendados por Haykin
 * (pág. 452).
 */
SOM::SOM() : eta(0.5), t2(1000), tol(1e-2)
{
	srand(time(NULL) + getpid());
}


/**
 * @brief Destructor.
 */
SOM::~SOM() {}


/**
 * @brief Fija la tasa de aprendizaje inicial de la red.
 * La misma es usada para ir actualizando la tasa de aprendizaje a lo largo
 * del tiempo.
 */
void SOM::set_tasa_inicial(double n)
{
	this->eta = n;
}


/**
 * @brief Fija el valor t usado para calcular la tasa de aprendizaje variable
 * con el tiempo.
 */
void SOM::set_t2(double t)
{
	this->t2 = t;
}


/**
 * @brief Fija el valor de sigma inicial (ancho de la vecindad).
 * El mismo es usado para calcular el valor de sigma variable con el tiempo
 * para la función de vecindad.
 */
void SOM::set_sigma_inicial(double s)
{
	this->sigma = s;
}


/**
 * @brief Fija el valor t usado para calcular el valor de sigma variable con
 * el tiempo para la función de vecindad.
 */
void SOM::set_t(double t)
{
	this->t = t;
}


/**
 * @brief Comprueba que se haya seteado una arquitectura y aborta la ejecución
 * en caso contrario.
 */
void SOM::verificar_inicializada()
{
	if (this->grilla.empty()){
		cout<<"No se configuró ninguna arquitectura para la red.\n";
		exit(-1);
	}
}


/**
 * @brief Inicializa el mapa con una matriz de neuronas de tamaño MxN.
 */
void SOM::inicializar(int M, int N)
{
	this->grilla = Matriz(M, vector<Neurona>(N));
	this->M = M;
	this->N = N;

	/* valores por defecto: si no se establecen valores específicos después,
	 * estos parámetros toman los valores recomendados por Haykin (pág. 453)
	 * para un grilla 2D:
	 * sigma: igual al "radio" de la grilla
	 * t: 1000/log(sigma)
	 */
	this->sigma = min(M, N)/2.0;
	this->t = 1000/log(this->sigma);
}


/**
 * @brief Inicializa todos los pesos de todas las neuronas de la red.
 */
void SOM::inicializar_pesos()
{
	for (int i=0; i<this->M; ++i){
		for (int j=0; j<this->N; ++j){
			this->grilla[i][j].inicializar_pesos(this->datos[0].size());
			this->grilla[i][j].set_position(pair<int,int> (i,j));
		}
	}
}


/**
 * @brief Busca la neurona ganadora para un patrón de entrada.
 * @param x Patrón de entrada.
 * @param i Por acá devuelve la fila de la neurona ganadora.
 * @param j Por acá devuelve la columna de la neurona ganadora.
 */
void SOM::competir(vector<double> &x, int &i, int &j)
{
	double win = numeric_limits<double>::max();
	int wini = -1, winj = -1;
	double aux;

	//recorro todas las neuronas y veo cuál da mayor producto interno con la entrada
	for (int f=0; f<this->M; ++f){
		for (int c=0; c<this->N; ++c){
			aux = this->grilla[f][c].evaluar(x);
			if (aux < win){
				win = aux;
				wini = f;
				winj = c;
			}
		}
	}
	//resultados
	i = wini; j = winj;
	
}


/**
 * @brief Actualiza los pesos de todas las neuronas según las reglas del SOM.
 *
 * A partir de la neurona ganadora para un patrón de entrada, se actualizan los
 * pesos usando una función de vecindad que depende de la distancia de la ganadora
 * hacia las demás.
 * 
 * @param iganadora Fila de la neurona ganadora.
 * @param jganadora Columna de la neurona ganadora.
 * @param x Patrón de entrada actual.
 * @param n Instante actual de tiempo discreto.
 */
void SOM::actualizar_pesos(int iganadora, int jganadora, vector<double> &x, int n)
{
	double r, h;
	double e = eta_variable(n, this->eta, this->t2);
	for (int i=0; i<this->M; ++i){
		for (int j=0; j<this->N; ++j){
			r = dist(iganadora, jganadora, i, j);
			//r = dist(grilla[iganadora][jganadora].position(), grilla[i][j].position());
			h = funcion_vecindad(n, r, this->sigma, this->t);
			//cout<<setw(9)<<h<<" | ";

			this->grilla[i][j].actualizar_pesos(x, e, h);
		}
		//cout<<endl;
	}
}


/**
 * @brief Entrena la red neuronal.
 * @param name Nombre del archivo que contiene los datos.
 */
void SOM::entrenar(const char *name)
{
	verificar_inicializada();
	
	//Abro el archivo de datos:
	vector<double> salidas_escalares;
	this->datos = leer_csv(name, salidas_escalares); ///<\todo ver si hay que meter el -1

	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo."<<endl; return;}

	//inicializo los pesos de la red
	inicializar_pesos();

	//vector con índices para aleatorizar entradas
	int cant_patrones_entrada = datos.size();
	vector<int> indices(cant_patrones_entrada);
	for (size_t i=0; i<indices.size(); ++i){
		indices[i] = i;
	}
	random_shuffle(indices.begin(), indices.end());

	//empiezo el entrenamiento
	int it = 0; //iteraciones
	int epocas = 0;
	double error=0;
	while (epocas < 50){ ///<\todo detener cuando no se observen cambios
		
		for (int i=0; i<cant_patrones_entrada; ++i){ //recorro todo el set de datos
		
			vector<double> &entrada = datos[indices[i]]; //un patrón de entrada (no todas)
			
			//busco la ganadora para este patrón de entrada
			int iwin, jwin;
			competir(entrada, iwin, jwin);

			//calculo el error
			error+=dist(entrada,grilla[iwin][jwin].get_pesos());
			
			//actualizar los pesos
			actualizar_pesos(iwin, jwin, entrada, it);

			visualizar_resultados();
			//wait(500);
			
			
			it++;
			
		}
		if((error/cant_patrones_entrada)<this->tol){ cout<<"corto por error"<<endl; break;}
		cout<<"Epoca numero "<<epocas<<" error para la epoca: "<<error/cant_patrones_entrada<<endl;
		epocas++;
		error=0;
		//if (!(epocas%10))

		
		//aleatorizar la presentación de patrones en la siguiente época
		random_shuffle(indices.begin(), indices.end());
	}
	//visualizar_resultados();


}

vector<vector<peso_act> > SOM::generar_datos_grafico(){
	vector<vector<peso_act> > Graf;
	vector<peso_act> aux;
	for(size_t i=0;i<grilla.size();i++) { 
		for(size_t j=0;j<grilla[i].size();j++) { 
			aux.push_back(grilla[i][j].devolver_peso_act());
		}
		Graf.push_back(aux);
		aux.clear();
	}
	return Graf;
}




void mapeo(double x, double y, double &xsalida, double &ysalida)
{
	int w = 800, h = 600;
	double xmin = -1, xmax = 1;
	double ymin = -1, ymax = 1;
	double nn = fabs(xmax-xmin);

	xsalida = (x - xmin)/nn; xsalida *= w;
	ysalida = (y - ymin)/nn; ysalida *= h;

}

void unir(double x, double y, double xv, double yv)
{
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2d(x, y);
		glVertex2d(xv, yv);
	glEnd();
}

/**
 * @brief Guarda los pesos de las neuronas entrenadas y muestra el mapa
 * topológico aprendido.
 */
void SOM::visualizar_resultados()
{
	glClear(GL_COLOR_BUFFER_BIT);

	double x, y, xv, yv;
	//plotter("set key off");
	//bool b = true;
	//int k=0;
	vector<double> p;
	
	for (int i=0; i<this->M; ++i){
		for (int j=0; j<this->N; ++j){

			p = this->grilla[i][j].get_pesos();
			mapeo(p[0], p[1], x, y);

			glColor3f(0,0,0); glPointSize(5);
			glBegin(GL_POINTS);
				glVertex2d(x, y);
			glEnd();

			//el de la derecha:
			if (i+1 < this->M){
				mapeo(this->grilla[i+1][j].get_pesos()[0],
					this->grilla[i+1][j].get_pesos()[1], xv, yv);
				unir(x, y, xv, yv);
			}

			//de la abajo:
			if (j+1 < this->N){
				mapeo(this->grilla[i][j+1].get_pesos()[0],
					this->grilla[i][j+1].get_pesos()[1], xv, yv);
				unir(x, y, xv, yv);
			}

		}
	}
	glutSwapBuffers();
	//cin.get();
	//remove("*.dat");
}




void SOM::visualizar_datoslabel(int cant_clases){
	//inicializo el vector de colores
	vector<vector<float> > color;
	inicializar_color(color,cant_clases);
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	double x, y, xv, yv;
	vector<double> p;
	
	for (int i=0; i<this->M; ++i){
		for (int j=0; j<this->N; ++j){
			
			//this->grilla[i][j].get_pesos();
			mapeo(i, j, x, y);
			
			int clase=this->grilla[i][j].get_clase();
			glColor3f(color[clase][0],color[clase][1],color[clase][2]);
			glBegin(GL_POINTS);
			glVertex2d(x, y);
			glEnd();
			
			//el de la derecha:
			if (i+1 < this->M){
				mapeo(i+1,j, xv, yv);
				unir(x, y, xv, yv);
			}
			
			//de la abajo:
			if (j+1 < this->N){
				mapeo(i,j+1, xv, yv);
				unir(x, y, xv, yv);
			}
			
		}
	}
	glutSwapBuffers();
}




void SOM::display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0); glPointSize(5);
	vector<vector<peso_act> > grafico = generar_datos_grafico();
	vector<vector<peso_act> >::iterator q=grafico.begin();
	while(q!=grafico.end()){
		for(size_t i=0;i<(*q).size();i++) { 
			peso_act *act=&(*q)[i];
			if(act->weight.size()==2){
				//setear_colores(act->cant_act);
				glBegin(GL_POINTS);
					glVertex2d(800*(act->weight[0]),600*(act->weight[1])); 
				glEnd();
				}
			
			
			else{
				//aca ver como hacer cuando tengo 3D, 4D, etc.
			}
		}
		
		q++;
	}

	
	glutSwapBuffers();
}
