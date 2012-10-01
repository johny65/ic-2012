#include <iostream>
#include <GL/glut.h>
#include "SOM.h"


using namespace std;

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
	som.entrenar("phoneme.csv");
	som.etiquetar("phoneme.csv");
	som.clasificar("phoneme.csv");

	cin.get();
	return 0;
}
