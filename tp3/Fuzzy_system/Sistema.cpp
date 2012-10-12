#include "Sistema.h"
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <cstdlib>
using namespace std;
Sistema::Sistema(vector<double> intervalos_t,vector<double> intervalos_i,vector<double> intervalos_v) { 
	/**
	@param cant_conj: cantidad de conjuntos difusos.
	@param intervalos de los conjuntos difusos (el tamanio del vector debe ser 2*cant conjuntos contiene los valores left y right de los triangulos)
	*/
	//cargo los triangulos de entrada
	triangulo aux;
	
	 
	//cargo los triangulos:
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
	
	//cargo los triangulos:
	for(int i=0;i<(intervalos_i.size()/2);i++) { 
		aux.left=intervalos_i[2*i];
		aux.right=intervalos_i[2*i+1];
		aux.calcular_centro();
		this->conjuntos_i.push_back(aux);
	}
	
	//cargo un ultimo medio triangulo
	aux=this->conjuntos_i.back();
	l=aux.center; //el left del medio triangulo debe ser igual al center de ultimo cargado
	aux.left=l; aux.center=aux.right;
	this->conjuntos_i.push_back(aux); //meto el ultimo medio triangulo, el right no me preocupa pues solo uso left y center;
	cout<<"triangulo de corriente"<<endl<<aux.left<<" "<<aux.center<<" "<<aux.right<<endl;
	
	
	//genero conjuntos de salida del voltaje.
	
	
	//cargo los triangulos:
	for(int i=0;i<(intervalos_v.size()/2);i++) { 
		aux.left=intervalos_v[2*i];
		aux.right=intervalos_v[2*i+1];
		aux.calcular_centro();
		this->conjuntos_v.push_back(aux);
	}
	
	//cargo un ultimo medio triangulo
	aux=this->conjuntos_v.back();
	l=aux.center; //el left del medio triangulo debe ser igual al center de ultimo cargado
	aux.left=l; aux.center=aux.right;
	this->conjuntos_v.push_back(aux); //meto el ultimo medio triangulo, el right no me preocupa pues solo uso left y center;
	
	
	
	//inicializo la temperatura exterior segun la figura que esta en la guia cada 10 minuto cambia cada valor representa 10 segundos
	for(int i=0;i<6;i++) { 
		double t_ext=10+rand()%30;
		for(int j=0;j<60;j++) { //constante durante 10 minutos;
			this->temp_ext.push_back(t_ext);
		}
	}
	
	
	//inicializo la temperatura de referencia
	for(int i=0;i<6;i++) { 
		for(int j=0;j<60;j++) {//cada 10 minutos cambia la temperatura 
			this->temp_ref.push_back(i%2==0 ? 18 : 22);
		}
		cout<<this->temp_ref.back()<<setw(5);
	}
	
	//elijo un numero aletorio entre 0 y 359 instante en el cual se habre la puerta;
	this->puerta_abierta=0+rand()%360;
	
	
	graficar_conjuntos();
}

Sistema::~Sistema() {
	
}

pair<int,int> Sistema::conjuntos_activados(double n){
	pair<int,int> r; r.first=-1; r.second=-1;
	for(int i=0;i<this->conjuntos_temp.size();i++) { 
		if(this->conjuntos_temp[i].pertenece(n)){
			if(r.first!=-1) r.second=i;
			else r.first=i;
		}
	}
	return r;
}

void Sistema::Simular_sincontrol(){
	this->temp_int_sc.push_back(20); ///<declaro la temperatura del interior inicial en 20 grados (solo para simular)
	for(int i=1;i<this->temp_ref.size();i++) {  
		if(i==this->puerta_abierta)
			this->temp_int_sc.push_back(0.169*this->temp_int_sc[i-1]+0.831*this->temp_ext[i]);
		else
			this->temp_int_sc.push_back(0.912*this->temp_int_sc[i-1]+0.088*this->temp_ext[i]);
	}
	graficar(this->temp_int_sc);
}

void Sistema::graficar_conjuntos(){
	crear_dat_conjuntos(this->conjuntos_temp,"conjunto_t.dat");
	crear_dat_conjuntos(this->conjuntos_i,"conjunto_i.dat");
	crear_dat_conjuntos(this->conjuntos_v,"conjunto_v.dat");
	crear_dat_vector(this->temp_ref,"temp_ref.dat");
	///<to do Graficar con GNUPLOT
}


void Sistema::graficar_controlado(){
	crear_dat_vector(this->temp_int_cc,"sistema_cc.dat");
	
}
void Sistema::graficar(vector<double> &T){
	crear_dat_vector(T,"sin_control.dat");
	ostringstream sp;
	crear_dat_vector(this->temp_ext,"temp_ext.dat");
	sp<<"plot \"sin_control.dat\" with lines"<<"\n";
	sp<<"replot \"temp_ext.dat\" with lines"<<"\n";
	plotter(sp.str());
	
}

void Sistema::Simular_concontrol(){
	///< Para la simulacion hacemos lo siguiente:
	///< tomamos la temperatura de refencia y la restamos de la temperatura exterior(entrada) Text-Tr=n
	///< Si n<0 tengo que prender la calefaccion (i:corriente)
	///< Si n>0 tengo que prender la refrigeracion (v: voltaje);
	
	//this->temp_ext.insert(temp_ext.begin(),40); ///solo para ir probando
	double n;
	double volt=0,corriente=0;
	double temp_interna;
	pair<int,int> conj_activo; //los dos conjuntos que se activan caso que se active solo 1 conj_activo.second=0;
	pair<double,double> grado_memb;//guardo los grados de membresia para los conjuntos de temperatura
	this->temp_int_cc.push_back(this->temp_ext.at(0)); ///< pongo el primer valor de la temperatura externa igual a la temperatura externa
	
	for(int i=1;i<this->temp_ext.size();i++) { 
		//Para cada temperatura exterior
		
		n=this->temp_ext[i]-this->temp_ref[i];
		//solo para depuracion:
		cout<<"temp_ext "<<this->temp_ext[i]<<" Temp_ref: "<<this->temp_ref[i]<<endl;
		cout<<"variables de decicion n: "<<n<<endl;
		
		
		if(n<0){ //debo activar la calefaccion
			n=abs(n);
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
			}
		}
		else if(n>0){//debo activar la refrigeracion
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
		}
		
		
		///<Aplico la formula para calcular la temperatura interior
		
		if(this->puerta_abierta==i) temp_interna=0.169*temp_int_cc.back()+0.831*temp_ext[i]+0.112*pow(corriente,2)-0.002*volt;
		else temp_interna=0.912*temp_int_cc.back()+0.088*temp_ext[i]+0.604*pow(corriente,2)-0.0121*volt;
		
		this->temp_int_cc.push_back(temp_interna); ///<guardo el valor de la temp_interna controlada
	}
	///<to do: rutinas para graficar
	graficar_controlado();
}

