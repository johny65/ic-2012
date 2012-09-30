#include <iostream>
#include <GL/glut.h>
#include "SOM.h"


using namespace std;


vector<vector<peso_act> > grafico;

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

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0,0,0); glPointSize(5);
	
	vector<vector<peso_act> >::iterator q=grafico.begin();
	while(q!=grafico.end()){
		for(size_t i=0;i<(*q).size();i++) { 
			peso_act *act=&(*q)[i];
			if(act->weight.size()==2){
				setear_colores(act->cant_act);
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

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (800,600);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Neuronas ganadoras");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
}



int main (int argc, char *argv[]) {
	SOM som;
	som.inicializar(10, 10);

	som.entrenar("rectangulo.csv");
	grafico=som.generar_datos_grafico();
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
