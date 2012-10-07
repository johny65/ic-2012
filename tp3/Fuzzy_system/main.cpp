#include<iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <vector>
#include "Sistema.h"
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

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (800,600);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Conjuntos Difusos");
	glutReshapeFunc (reshape_cb);
	
	reshape_cb(800,600);
	glClearColor(1.f,1.f,1.f,1.f);
	glutSwapBuffers();
}

int main (int argc, char *argv[]) {
	glutInit (&argc, argv);
	initialize();
	double a[18]={0.0, 0.2, 0.1, 0.3, 0.2, 0.4, 0.3, 0.5, 0.4, 0.6, 0.5, 0.7, 0.6, 0.8, 0.7, 0.9, 0.8, 1.0};
	vector<double> B (a,a+sizeof(a)/sizeof(double));
	Sistema Temp(9,B);
	
	
//	cin.get();
	
	return 0;
}

