#include <iostream>
#include "simulation.hpp"
#include "physics.hpp"
#include "omp.h"
#include <GL/glut.h>

using namespace std;

// static float TOTAL_TIME = 4.0;

// vector<starling> murmuration;
environment env;

int refreshMills = 100;        // refresh interval in milliseconds [NEW]
int temp = 0;

void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}


void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void display(void)
{	
	position p;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	//draw two points
	glBegin(GL_POINTS);
	// cout << env.num << endl;
	for(int i = 0; i < env.num; i++)
	{	
		p = env.murmuration[i].pos_old;
		glVertex2f(p.x + temp ,p.y + temp);
		cout << p.x << " " << p.y << endl;
	}
	glEnd();

	// //draw a line
	// glBegin(GL_LINES);
	// 	glVertex2i(10,10);
	// 	glVertex2i(100,100);
	// glEnd();

	glFlush();

	env.update();
	env.handle_intersection();
	env.display_energy();
	
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
	glutCreateWindow ("points and lines");
	init2D(0.0,0.0,0.0);
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]	
	glutMainLoop();

	return 0;
}