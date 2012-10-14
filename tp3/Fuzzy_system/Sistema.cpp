#include "Sistema.h"
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <cstdlib>

using namespace std;

Sistema::Sistema(vector<double> intervalos_t, vector<double> intervalos_i,
	vector<double> intervalos_v) {
		
	/**
	@param intervalos de los conjuntos difusos (el tamaño del vector debe ser
	 2*cant conjuntos, contiene los valores left y right de los triangulos)
	*/
	srand(time(NULL));

	//cargo los triángulos de temperatura:
	triangulo aux;
	for(int i=0;i<(intervalos_t.size()/2);i++) { 
		aux.left=intervalos_t[2*i];
		aux.right=intervalos_t[2*i+1];
		aux.calcular_centro();
		this->conjuntos_temp.push_back(aux);
	}
	
	//cargo un ultimo medio triangulo
	aux=this->conjuntos_temp.back();
	double l=aux.center; //el left del medio triangulo debe ser igual al center de ultimo cargado
	aux.left=l; aux.center=aux.right;
	this->conjuntos_temp.push_back(aux); //meto el ultimo medio triangulo, el right no me preocupa pues solo uso left y center;
	
	
	//genero conjuntos de salida de la corriente
	
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
	
	//graficar_conjuntos();
}



Sistema::~Sistema() {
	
}

pair<int,int> Sistema::conjuntos_activados(double n){
	pair<int,int> r; r.first=-1; r.second=-1;
	for(size_t i=0;i<this->conjuntos_temp.size();i++) { 
		if(this->conjuntos_temp[i].pertenece(n)){
			if(r.first!=-1) r.second=i;
			else r.first=i;
		}
	}
	return r;
}

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

void Sistema::graficar_conjuntos(){
	//crear_dat_conjuntos(this->conjuntos_temp,"conjunto_t.dat");
	crear_dat_conjuntos(this->conjuntos_i,"conjunto_i.dat");
	crear_dat_conjuntos(this->conjuntos_v,"conjunto_v.dat");
	crear_dat_conjuntos(this->conjuntos_te,"conjunto_te.dat");
	crear_dat_conjuntos(this->conjuntos_var,"conjunto_var.dat");
	
	///<\todo Graficar con GNUPLOT
	
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

void Sistema::Simular_concontrol(){
	///< Para la simulacion hacemos lo siguiente:
	/**< tomamos la temperatura de refencia y la restamos de la temperatura \
	 exterior(entrada) Text-Tr=n */
	///< Si n<0 tengo que prender la calefaccion (i:corriente)
	///< Si n>0 tengo que prender la refrigeracion (v: voltaje);
	
	//this->temp_ext.insert(temp_ext.begin(),40); ///solo para ir probando
	double n;
	double volt=0,corriente=0;
	double temp_interna;
	pair<int,int> conj_activo; //los dos conjuntos que se activan caso que se active solo 1 conj_activo.second=-1;
	pair<double,double> grado_memb;//guardo los grados de membresia para los conjuntos de temperatura
	//this->temp_int_cc.push_back(this->temp_ext.at(0)); ///< pongo el primer valor de la temperatura externa igual a la temperatura externa
	this->temp_int_cc.push_back(18+rand()%5); ///< pongo el primer valor de la temperatura externa igual a la temperatura externa

	vector<double> var, cor, vol;
	
	for(size_t i=1;i<this->temp_ext.size();i++) { 
		//Para cada temperatura exterior
		
		n=this->temp_int_cc.back()-this->temp_ref[i];
		var.push_back(n);
		//solo para depuracion:
		//cout<<"temp_ext "<<this->temp_ext[i]<<" Temp_ref: "<<this->temp_ref[i]<<endl;
		//cout<<"variables de decicion n: "<<n<<endl;
		
		//if (fabs(n) < 0.5){
			//corriente = cor.back();
			//volt = vol.back();
		//}
		if(n<0){ //debo activar la calefaccion
			n=fabs(n);
			vector<trapezoide> escalados;
			//escalados.push_back(verificar_regla(BAJA, MUYPOCA, BAJA, 'i',
				//this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, POCA, MEDIA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, MEDIANA, MEDIA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, MUCHA, ALTA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, MUCHISIMA, ALTA, 'i',
				this->temp_ext[i], n));
			//escalados.push_back(verificar_regla(MEDIA, MUYPOCA, MEDIA, 'i',
				//this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, POCA, BAJA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, MEDIANA, MEDIA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, MUCHA, ALTA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, MUCHISIMA, ALTA, 'i',
				this->temp_ext[i], n));

					//CAMBIADA TODAS
			//escalados.push_back(verificar_regla(ALTA, MUYPOCA, ALTA, 'i',
				//this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, POCA, BAJA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, MEDIANA, BAJA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, MUCHA, MEDIA, 'i',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, MUCHISIMA, ALTA, 'i',
				this->temp_ext[i], n));
			
			//defuzzyficar:
			corriente = Defuzzification(escalados);
			volt = 0.0;


			/*
			conj_activo=conjuntos_activados(n);
			///<aca podria aplicar un mapeo con map por ahora supongo que tengo la misma cantidad de conjuntos en la salida que en la entrada
			if(conj_activo.second!=-1){ ///<si se activaron dos conjuntos
				grado_memb.first=this->conjuntos_temp.at(conj_activo.first).calcular_degree(n);
				grado_memb.second=this->conjuntos_temp.at(conj_activo.second).calcular_degree(n);
				this->conjuntos_i.at(conj_activo.first).calcular_bc(grado_memb.first); //calculos los trapezoides
				this->conjuntos_i.at(conj_activo.second).calcular_bc(grado_memb.second); //calculo los trapezoides
				corriente=calcular_centroide(this->conjuntos_i.at(conj_activo.first).A,this->conjuntos_i.at(conj_activo.second).A);
				//volt=0;
				cout<<"valor de la corriente "<<corriente<<endl;
				cout<<"conjuntos activos "<<conj_activo.first<<"  "<<conj_activo.second<<endl;
				cout<<"grado de activacion "<<grado_memb.first<<"  "<<grado_memb.second<<endl;
			}
			else{///<solo se activo un conjunto
				grado_memb.first=this->conjuntos_temp.at(conj_activo.first).calcular_degree(n);
				this->conjuntos_i.at(conj_activo.first).calcular_bc(grado_memb.first); //calculos los trapezoides
				corriente=calcular_centroide_unico(this->conjuntos_i.at(conj_activo.first)); ///<to do: Validar centroides unico el unico que puede ser es el que cae en 0 
				//volt=0;
			}*/
		}
		else if(n>0){//debo activar la refrigeracion
			n=fabs(n);
			vector<trapezoide> escalados;
			//escalados.push_back(verificar_regla(BAJA, MUYPOCA, BAJA, 'v',
				//this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, POCA, BAJA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, MEDIANA, BAJA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, MUCHA, MEDIA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(BAJA, MUCHISIMA, MEDIA, 'v',
				this->temp_ext[i], n));
			//escalados.push_back(verificar_regla(MEDIA, MUYPOCA, MEDIA, 'v',
				//this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, POCA, MEDIA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, MEDIANA, MEDIA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, MUCHA, ALTA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(MEDIA, MUCHISIMA, ALTA, 'v',
				this->temp_ext[i], n));

				//CAMBIADA ERA BAJA
			//escalados.push_back(verificar_regla(ALTA, MUYPOCA, BAJA, 'v',
				//this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, POCA, ALTA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, MEDIANA, ALTA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, MUCHA, ALTA, 'v',
				this->temp_ext[i], n));
			escalados.push_back(verificar_regla(ALTA, MUCHISIMA, ALTA, 'v',
				this->temp_ext[i], n));

			//defuzzyficar:
			volt = Defuzzification(escalados);

			corriente = 0.0;
			/*
			conj_activo=conjuntos_activados(n);
			///<aca podria aplicar un mapeo con map por ahora supongo que tengo la misma cantidad de conjuntos en la salida que en la entrada
			if(conj_activo.second!=-1){ ///<si se activaron dos conjuntos
				grado_memb.first=this->conjuntos_temp.at(conj_activo.first).calcular_degree(n);
				grado_memb.second=this->conjuntos_temp.at(conj_activo.second).calcular_degree(n);
				this->conjuntos_v.at(conj_activo.first).calcular_bc(grado_memb.first); //calculos los trapezoides
				this->conjuntos_v.at(conj_activo.second).calcular_bc(grado_memb.second); //calculo los trapezoides
				volt=calcular_centroide(this->conjuntos_v.at(conj_activo.first).A,this->conjuntos_v.at(conj_activo.second).A);
				//corriente=0;
				cout<<"valor del voltaje " <<volt<<endl;
				cout<<"conjuntos activos "<<conj_activo.first<<"  "<<conj_activo.second<<endl;
				cout<<"grado de activacion "<<grado_memb.first<<"  "<<grado_memb.second<<endl;
			}
			else{///<solo se activo un conjunto
				grado_memb.first=this->conjuntos_temp.at(conj_activo.first).calcular_degree(n);
				this->conjuntos_v.at(conj_activo.first).calcular_bc(grado_memb.first); //calculos los trapezoides
				volt=calcular_centroide_unico(this->conjuntos_v.at(conj_activo.first)); ///<to do: Validar centroides unico el unico que puede ser es el que cae en 0 
				//corriente=0;
			}
			*/
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
	///<to do: rutinas para graficar

	graficar_controlado();
	graficar_historia(var, cor, vol);
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
		cout<<"No se activó la regla\n";
		return T;
	}

	triangulo conjunto3;
	if (c == 'i')
		conjunto3 = this->conjuntos_i.at(C);
	else if (c == 'v')
		conjunto3 = this->conjuntos_v.at(C);

	conjunto3.calcular_bc(comp);
	cout<<"Para n="<<a2<<" se activó el conjunto "<<A2<<" con "<<activacion2<<endl;
	cout<<"Para TE="<<a1<<" se activó el conjunto "<<A1<<" con "<<activacion1<<endl;
	
	return conjunto3.A;
	
}


void Sistema::set_conjuntos(vector<double> &te, vector<double> &var)
{
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
	
	graficar_conjuntos();
	
}


void Sistema::Fuzzification()
{
}


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

void Sistema::graficar_historia(vector<double> &n, vector<double> &i, vector<double> &v)
{
	crear_dat_vector(n, "historia_var.dat");
	crear_dat_vector(i, "historia_i.dat");
	crear_dat_vector(v, "historia_v.dat");
	plotter_var("set title \"Variación\"; plot \"historia_var.dat\" with lines");
	plotter_i("set title \"Corriente\"; plot \"historia_i.dat\" with lines");
	plotter_v("set title \"Voltaje\"; plot \"historia_v.dat\" with lines");
}
