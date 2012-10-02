#include <iostream>
#include <GL/glut.h>
#include "SOM.h"


using namespace std;
string name;
int pantalla(){
	int op;
	cout<< "Que desea Hacer? "<<endl;
	cout<< "1- Entrenar un SOM (problema de entrenamiento sin clasificacion)"<<endl;
	cout<< "2- Utilizar un SOM como clasificador"<<endl;
	cin>> op;
	cout<<"Por favor introduzca el nombre del archivo .csv"<<endl;
	cin>> name;
	return op;
}


void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void setear_colores(int &act){
	float r,g,b;
	r=(30*act)/100.0;
	g=0.1;
	b=0.1;
	glColor3f(r,g,b);
	glPointSize(5.00);
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (800,600);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Mapa Autoorganizativo - Entrenamiento");
	glutReshapeFunc (reshape_cb);
	reshape_cb(800,600);
	glClearColor(1.f,1.f,1.f,1.f);
	glutSwapBuffers();
}



int main (int argc, char *argv[]) {
	glutInit (&argc, argv);
	initialize();

	SOM som;
	som.inicializar(10, 10);
	int opcion=pantalla();
	if(opcion==1){
		som.set_view(true);
		som.entrenar(name.c_str()); 
		cin.get();}
	if(opcion==2){
		som.set_view(false); //para clasificacion no muestro como se ajusta el som en el entrenamiento
		som.entrenar(name.c_str());
		som.etiquetar(name.c_str());
		som.clasificar(name.c_str());
		cin.get();
	}
	

	cin.get();
	return 0;
}
