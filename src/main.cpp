#include <iostream>
#include "simulation.hpp"
#include "physics.hpp"
#include "omp.h"
#include <GL/glut.h>
#include <unistd.h>
#include <cmath>

using namespace std;

environment env;
int mainwindow;


void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void updates(void){
	env.update();
	env.handle_intersection();
	env.display_energy();
	glutSetWindow(mainwindow);
	glutPostRedisplay();
	// usleep(10000);
}

void display(void)
{	
	position p;
	velocity v;
	float mod;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	//draw two points
	glBegin(GL_POINTS);
	// cout << env.num << endl;
	for(int i = 0; i < env.num; i++)
	{	
		p = env.murmuration[i].pos_new;
		v = env.murmuration[i].v_new;
		mod = sqrt(v.v_x*v.v_x + v.v_y*v.v_y);
		
		glVertex2f(p.x, p.y);
		cout << p.x << " " << p.y << endl;
		// glBegin(GL_LINE);
		// glVertex2f(p.x, p.y);
		// glVertex2f(p.x + 10.0*v.v_x/mod, p.y + 10.0*v.v_y/mod);
		// glEnd();
	}
	glEnd();

	glBegin(GL_LINES);
	for(int i = 0; i < env.num; i++)
	{	
		p = env.murmuration[i].pos_new;
		v = env.murmuration[i].v_new;
		mod = sqrt(v.v_x*v.v_x + v.v_y*v.v_y);
		
		glVertex2f(p.x, p.y);
		glVertex2f(p.x + 5.0*v.v_x/mod, p.y + 5.0*v.v_y/mod);
	}
	glEnd();

	glFlush();

	
}

int main(int argc,char *argv[]){
	
	// environment env;
	int n; 
	cout << "Enter number of birds: ";
	cin >> n;
	cout << "\n";

	env.num = n;
	env.init_environment();
	
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1000, 1000);
	glutInitWindowPosition (0, 0);
	mainwindow = glutCreateWindow ("points and lines");
	init2D(0.0,0.0,0.0);
	glutDisplayFunc(display);
	// glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]	
	glutIdleFunc(updates);
	glutMainLoop();

	return 0;
}