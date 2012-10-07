#include "Sistema.h"
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
using namespace std;
Sistema::Sistema(int cant_conj,vector<double> intervalos) { 
	/**
	@param cant_conj: cantidad de conjuntos difusos.
	@param intervalos de los conjuntos difusos (el tamanio del vector debe ser 2*cant conjuntos contiene los valores left y right de los triangulos)
	*/
	triangulo aux;
	for(int i=0;i<cant_conj;i+=2) { 
		aux.left=intervalos[i];
		aux.right=intervalos[i+1];
		this->conjuntos.push_back(aux);
	}
	
	//inicializo la temperatura exterior en forma aletoria doy valores entre -10 y 50 grados. cada valor representa 10 segundos
	for(int i=0;i<12;i++) { 
		double aux=-10+rand()%60;
		for(int j=0;j<30;j++) {  //mantengo por 5 minutos el mismo valor de temperatura exterior
			this->temp_ext.push_back(aux);
		}
		cout<<this->temp_ext.back()<<setw(5);
	}
	cout<<endl;
	
	//inicializo la temperatura de referencia
	for(int i=0;i<6;i++) { 
		for(int j=0;j<60;j++) {//cada 10 minutos cambia la temperatura 
			this->temp_ref.push_back(i%2==0 ? 18 : 22);
		}
		cout<<this->temp_ref.back()<<setw(5);
	}
}

Sistema::~Sistema() {
	
}

void Sistema::graficar_conjuntos(){
	glClear(GL_COLOR_BUFFER_BIT);
	//Grafico los conjuntos
	glColor3f(1.0,0.0,0.0); glPointSize(80);
	for(size_t i=0;i<this->conjuntos.size();i++) { 
		triangulo *aux=&(this->conjuntos[i]);
		glBegin(GL_LINES);
			glVertex2d(100*aux->left,0.0); glVertex2d(100*aux->center,100.0);
			glVertex2d(100*aux->center,100.0); glVertex2d(100*aux->right,0.0);
		glEnd();	
	}
	glutSwapBuffers();
}

