#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "Sistema.h"

//para reducir código:
#define ifthen_corriente(x, y, z) regla_corriente(x, y, z, this->temp_ext[i], n, truncados)
#define ifthen_voltaje(x, y, z) regla_voltaje(x, y, z, this->temp_ext[i], n, truncados)


using namespace std;

/**
 * @brief Constructor.
 * @param Intervalos de los conjuntos difusos (el tamaño del vector debe ser
 * 2*cant conjuntos, contiene los valores left y right de los triangulos)
 */
Sistema::Sistema(vector<double> &intervalos_i, vector<double> &intervalos_v,
	vector<double> &intervalos_te, vector<double> &intervalos_var)
{
	srand(time(NULL));

	
	//genero conjuntos de salida de la corriente
	
	triangulo aux;
	aux.left = intervalos_i[0];
	aux.right = intervalos_i[1];
	//aux.center = aux.left;
	aux.calcular_centro();
	this->conjuntos_i.push_back(aux);
	
	for(size_t i=1; i<(intervalos_i.size()/2); ++i){
		aux.left = intervalos_i[2*i];
		aux.right = intervalos_i[2*i+1];
		aux.calcular_centro();
		this->conjuntos_i.push_back(aux);
	}
	//this->conjuntos_i.back().center = this->conjuntos_i.back().right;
	
	
	//genero conjuntos de salida del voltaje.
	
	aux.left = intervalos_v[0];
	aux.right = intervalos_v[1];
	//aux.center = aux.left;
	aux.calcular_centro();
	this->conjuntos_v.push_back(aux);
	
	for(size_t i=1; i<(intervalos_v.size()/2); ++i){
		aux.left = intervalos_v[2*i];
		aux.right = intervalos_v[2*i+1];
		aux.calcular_centro();
		this->conjuntos_v.push_back(aux);
	}
	//this->conjuntos_v.back().center = this->conjuntos_v.back().right;


	//conjuntos de entrada:
	set_conjuntos(intervalos_te, intervalos_var);
	
	//inicializo la temperatura exterior segun la figura que esta en la guia
	//cada 10 minuto cambia (cada valor representa 10 segundos)
	for(int i=0;i<6;i++){
		double t_ext = 10+rand()%30;
		for(int j=0;j<60;j++){ //constante durante 10 minutos;
			this->temp_ext.push_back(t_ext);
		}
	}
	
	
	//inicializo la temperatura de referencia
	for(int i=0;i<6;i++) { 
		for(int j=0;j<60;j++) {//cada 10 minutos cambia la temperatura 
			this->temp_ref.push_back(i%2==0 ? 18 : 22);
		}
		//cout<<this->temp_ref.back()<<setw(5);
	}
	
	//elijo un numero aletorio entre 0 y 359 instante en el cual se habre la puerta;
	this->puerta_abierta = rand()%360;
	
}


/**
 * @brief Destructor.
 */
Sistema::~Sistema() {}


/**
 * @brief Simula el sistema sin ningún control.
 */
void Sistema::Simular_sincontrol(){
	this->temp_int_sc.push_back(20); ///<declaro la temperatura del interior inicial en 20 grados (solo para simular)
	for(size_t i=1; i<this->temp_ref.size(); i++){
		if((int)i==this->puerta_abierta)
			this->temp_int_sc.push_back(0.169*this->temp_int_sc[i-1]+0.831*this->temp_ext[i]);
		else
			this->temp_int_sc.push_back(0.912*this->temp_int_sc[i-1]+0.088*this->temp_ext[i]);
	}
	graficar(this->temp_int_sc);
}


/**
 * @brief Simula el sistema con control.
 *
 * Para la simulacion hacemos lo siguiente:
 * Tomamos la temperatura de refencia y la restamos de la temperatura interna:
 *     Tint - Tr = n
 * Si n<0 tengo que prender la calefacción (i:corriente)
 * Si n>0 tengo que prender la refrigeración (v: voltaje).
 */
void Sistema::Simular_concontrol()
{
	double n;
	double volt=0,corriente=0;
	double temp_interna;
	//pongo el primer valor de la temperatura interna igual a la temperatura externa:
	this->temp_int_cc.push_back(this->temp_ext.at(0));

	vector<double> var, cor, vol; //para guardar la historia
	
	for(size_t i=1;i<this->temp_ext.size();i++) { 
		//Para cada temperatura exterior
		
		n = this->temp_int_cc.back() - this->temp_ref[i];
		var.push_back(n);
		
		//if (fabs(n) < 0.5){
			//corriente = cor.back();
			//volt = vol.back();
		//}
		if(n<0){ //debo activar la calefaccion
			n=fabs(n);
			vector<trapezoide> truncados;

			//ifthen_corriente: TEMP.EXTERNA, VARIACIÓN INT-REF -> CORRIENTE
			
			ifthen_corriente(BAJA, POCA, MEDIA);
			ifthen_corriente(BAJA, MEDIANA, MEDIA);
			ifthen_corriente(BAJA, MUCHA, ALTA);
			ifthen_corriente(BAJA, MUCHISIMA, ALTA);
			ifthen_corriente(MEDIA, POCA, BAJA);
			ifthen_corriente(MEDIA, MEDIANA, MEDIA);
			ifthen_corriente(MEDIA, MUCHA, ALTA);
			ifthen_corriente(MEDIA, MUCHISIMA, ALTA);
			ifthen_corriente(ALTA, POCA, BAJA);
			ifthen_corriente(ALTA, MEDIANA, BAJA);
			ifthen_corriente(ALTA, MUCHA, MEDIA);
			ifthen_corriente(ALTA, MUCHISIMA, ALTA);
			
			//defuzzyficar:
			corriente = Defuzzification(truncados);
			volt = 0.0;
		}
		else if(n>0){//debo activar la refrigeracion
		
			n=fabs(n);
			vector<trapezoide> truncados;

			//ifthen_voltaje: TEMP.EXTERNA, VARIACIÓN INT-REF -> VOLTAJE
			
			ifthen_voltaje(BAJA, POCA, BAJA);
			ifthen_voltaje(BAJA, MEDIANA, BAJA);
			ifthen_voltaje(BAJA, MUCHA, MEDIA);
			ifthen_voltaje(BAJA, MUCHISIMA, MEDIA);
			ifthen_voltaje(MEDIA, POCA, MEDIA);
			ifthen_voltaje(MEDIA, MEDIANA, MEDIA);
			ifthen_voltaje(MEDIA, MUCHA, ALTA);
			ifthen_voltaje(MEDIA, MUCHISIMA, ALTA);
			ifthen_voltaje(ALTA, POCA, ALTA);
			ifthen_voltaje(ALTA, MEDIANA, ALTA);
			ifthen_voltaje(ALTA, MUCHA, ALTA);
			ifthen_voltaje(ALTA, MUCHISIMA, ALTA);

			//defuzzyficar:
			volt = Defuzzification(truncados);
			corriente = 0.0;

		}
		
		///<Aplico la formula para calcular la temperatura interior
		
		if(this->puerta_abierta==(int)i){
			temp_interna = 0.169*temp_int_cc.back() + 0.831*temp_ext[i] +
				0.112*pow(corriente,2) - 0.002*volt;
		}
		else {
			temp_interna = 0.912*temp_int_cc.back() + 0.088*temp_ext[i] +
				0.604*pow(corriente,2) - 0.0121*volt;
		}
		
		this->temp_int_cc.push_back(temp_interna); ///<guardo el valor de la temp_interna controlada
		cor.push_back(corriente);
		vol.push_back(volt);
	}

	graficar_historia(var, cor, vol);
	graficar_controlado();
}


/**
 * @brief Verifica el grado de activación de una regla para los valores de
 * entrada (supone que los antecedentes están conectados mediante un AND).
 *
 * Verifica la regla "IF A1 AND A2 THEN C", o (A1, A2; C)
 * 
 * @param A1 Conjunto difuso del antecedente 1.
 * @param A2 Conjunto difuso del antecedente 2.
 * @param C Conjunto difuso del consecuente.
 * @param c Indica el conjunto del consecuente ('i' para corriente, 'v' para
 * voltaje).
 * @param a1 Valor de entrada para el antecedente 1.
 * @param a2 Valor de entrada para el antecedente 2.
 * @return El valor de activación del consecuente.
 */
trapezoide Sistema::verificar_regla(int A1, int A2, int C, char c, double a1, double a2)
{
	triangulo &conjunto1 = this->conjuntos_te.at(A1);
	double activacion1 = conjunto1.calcular_degree(a1);

	triangulo &conjunto2 = this->conjuntos_var.at(A2);
	double activacion2 = conjunto2.calcular_degree(a2);

	double comp = min(activacion1, activacion2);
	if (comp == 0.0){ //no se activó la regla
		trapezoide T;
		T.degree = 0.0;
		//cout<<"No se activó la regla\n";
		return T;
	}

	triangulo conjunto3;
	if (c == 'i')
		conjunto3 = this->conjuntos_i.at(C);
	else if (c == 'v')
		conjunto3 = this->conjuntos_v.at(C);

	conjunto3.calcular_bc(comp);
	//cout<<"Para n="<<a2<<" se activó el conjunto "<<A2<<" con "<<activacion2<<endl;
	//cout<<"Para TE="<<a1<<" se activó el conjunto "<<A1<<" con "<<activacion1<<endl;
	
	return conjunto3.A;
	
}


/**
 * @brief Verifica la activación de una regla para la corriente y si se activa
 * guarda el trapezoide en v.
 */
void Sistema::regla_corriente(int A1, int A2, int C, double te, double var,
	vector<trapezoide> &v)
{
	trapezoide salida = verificar_regla(A1, A2, C, 'i', te, var);
	if (salida.degree != 0.0){
		v.push_back(salida);
	}
}


/**
 * @brief Verifica la activación de una regla para el voltaje y si se activa
 * guarda el trapezoide en v.
 */
void Sistema::regla_voltaje(int A1, int A2, int C, double te, double var,
	vector<trapezoide> &v)
{
	trapezoide salida = verificar_regla(A1, A2, C, 'v', te, var);
	if (salida.degree != 0.0){
		v.push_back(salida);
	}
}


/**
 * @brief Establece los conjuntos difusos de entrada (temperatura externa y
 * diferencia de temperatura interna con temperatura referencia).
 */
void Sistema::set_conjuntos(vector<double> &te, vector<double> &var)
{
	/* conjuntos difusos de temperatura externa: */
	
	triangulo aux;
	aux.left = te[0];
	aux.right = te[1];
	//aux.center = aux.left;
	aux.calcular_centro();
	this->conjuntos_te.push_back(aux);
	
	for(size_t i=1; i<(te.size()/2); ++i){
		aux.left = te[2*i];
		aux.right = te[2*i+1];
		aux.calcular_centro();
		this->conjuntos_te.push_back(aux);
	}
	//this->conjuntos_te.back().center = this->conjuntos_te.back().right;

	
	/* conjuntos difusos de diferencia de temperatura: */
	
	aux.left = var[0];
	aux.right = var[1];
	//aux.center = aux.left;
	aux.calcular_centro();
	this->conjuntos_var.push_back(aux);
	for(size_t i=1; i<(var.size()/2); ++i){
		aux.left = var[2*i];
		aux.right = var[2*i+1];
		aux.calcular_centro();
		this->conjuntos_var.push_back(aux);
	}
	//this->conjuntos_var.back().center = this->conjuntos_var.back().right;
	
}


/**
 * @brief Defuzzifica un conjunto difuso.
 *
 * Devuelve una salida real obtenida mediante el cálculo del centroide de un
 * conjunto difuso que es la unión de varios conjuntos difusos (trapezoides).
 *
 * @param v Vector con los distintos trapezoides que forman el conjunto de salida.
 */
double Sistema::Defuzzification(vector<trapezoide> &v)
{
	double a = 0.0, b = 0.0;
	for (size_t i=0; i<v.size(); ++i){
		if (v[i].degree != 0.0){ //regla activada
			double centro = (v[i].d - v[i].a)/2.0 + v[i].a;
			a += centro * v[i].degree;
			b += v[i].degree;
		}
	}
	if (b == 0.0) return 0.0;
	return a/b;
}


/**
 * @brief Grafica los valores de corriente, voltaje y diferencia de temperaturas
 * a lo largo del tiempo.
 * 
 * @param n Vector con las diferencias de temperatura.
 * @param i Vector con las corrientes.
 * @param v Vector con los voltajes.
 */
void Sistema::graficar_historia(vector<double> &n, vector<double> &i, vector<double> &v)
{
	crear_dat_vector(n, "historia_var.dat");
	crear_dat_vector(i, "historia_i.dat");
	crear_dat_vector(v, "historia_v.dat");
	plotter_var("set title \"Variación\"; plot \"historia_var.dat\" with lines");
	plotter_i("set title \"Corriente\"; plot \"historia_i.dat\" with lines");
	plotter_v("set title \"Voltaje\"; plot \"historia_v.dat\" with lines");
}


/**
 * @brief Grafica los distintos conjuntos difusos para cada universo de discurso.
 */
void Sistema::graficar_conjuntos(){
	crear_dat_conjuntos(this->conjuntos_i,"conjunto_i.dat");
	crear_dat_conjuntos(this->conjuntos_v,"conjunto_v.dat");
	crear_dat_conjuntos(this->conjuntos_te,"conjunto_te.dat");
	crear_dat_conjuntos(this->conjuntos_var,"conjunto_var.dat");
	
	string s = "set xlabel \"Temperatura externa\"; plot [10:40] \"conjunto_te.dat\" with lines";
	plotter_t(s.c_str());
	s = "set xlabel \"Corriente\"; plot [0:3] \"conjunto_i.dat\" with lines";
	plotter_i(s.c_str());
	s = "set xlabel \"Voltaje\"; plot [0:220] \"conjunto_v.dat\" with lines";
	plotter_v(s.c_str());
	s = "set xlabel \"Variación interna-referencia\"; plot [0:30] \"conjunto_var.dat\" with lines";
	plotter_var(s.c_str());

	cin.get();
}


/**
 * @brief Grafica la simulación del sistema con control.
 */
void Sistema::graficar_controlado(){
	crear_dat_vector(this->temp_int_cc,"sistema_cc.dat");
	crear_dat_vector(this->temp_ext, "temp_ext.dat");
	crear_dat_vector(this->temp_ref, "temp_ref.dat");
	stringstream sp;
	sp<<"plot \"sistema_cc.dat\" with lines, ";
	sp<<"\"temp_ext.dat\" with lines, ";
	sp<<"\"temp_ref.dat\" with lines";
	plotter(sp.str().c_str());
}

/**
 * @brief Grafica la simulación del sistema sin control.
 */
void Sistema::graficar(vector<double> &T){
	crear_dat_vector(T,"sin_control.dat");
	ostringstream sp;
	crear_dat_vector(this->temp_ext, "temp_ext.dat");
	crear_dat_vector(this->temp_ref, "temp_ref.dat");
	sp<<"set ylabel \"Temperatura (C)\"\n";
	sp<<"plot \"sin_control.dat\" with lines"<<"\n";
	sp<<"replot \"temp_ext.dat\" with lines"<<"\n";
	sp<<"replot \"temp_ref.dat\" with lines"<<"\n";
	plotter(sp.str());
}
