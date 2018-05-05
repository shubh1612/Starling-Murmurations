#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "omp.h"
#include "physics.hpp"
#include "simulation.hpp"

using namespace std;

static float E_INITIAL = 100000000;
static float MEAN_XY = 500;  
static float MEAN_Z = 50;
static float VAR_POSXY = 100;
static float VAR_POSZ = 20;
static float MEAN_VEL = 40; 
static float VAR_VEL = 10; 
static float TIME_STEP = 5; 


void environment::init_environment(void){

	time_step = TIME_STEP;

	murmuration.resize(num);
	default_random_engine generator1, generator2, generator3;
	// normal_distribution<float> distribution1(MEAN_XY, VAR_POSXY);
	// normal_distribution<float> distribution2(MEAN_Z, VAR_POSZ);
	// normal_distribution<float> distribution3(MEAN_VEL, VAR_VEL);
	uniform_real_distribution<float> distribution1(0, 1000);
	uniform_real_distribution<float> distribution2(0, 100);
	// uniform_real_distribution<float> distribution3(MEAN_VEL, VAR_VEL);
	normal_distribution<float> distribution3(MEAN_VEL, VAR_VEL);

	#pragma omp parallel for
	for(int i = 0; i < num; i++)
	{
		starling c;
		position p;
		velocity v;

		/***Initializing position, velocity and energy***/
		float number = distribution1(generator1);
		p.x = number;
		float number1 = distribution1(generator1);
		p.y = number1;
		float number2 = distribution2(generator2);
		p.z = number2;

		float number3 = distribution3(generator3);
		v.v_x = number3;
		number3 = distribution3(generator3);
		v.v_y = number3;
		number3 = distribution3(generator3);
		v.v_z = number3;

		c.E_mech_old = E_INITIAL; /**some value **/
		c.pos_new = p;
		c.v_new = v;

		murmuration[i] = c;
	}
}

void environment::update(void){
	double start = omp_get_wtime();
	// #pragma omp parallel for
	for(int i = 0 ; i < num; i++){
		murmuration[i].get_neighbours(murmuration);
		murmuration[i].update_velocity(murmuration);
		murmuration[i].update_position(time_step);
		// murmuration[i].update_stored_energy();
		// murmuration[i].pos_new.x++;	
	
	}
	// cout << omp_get_wtime() - start << endl;
}

void environment::handle_intersection(void){

}

void environment::simulate(void){

	// glutInit(NULL,NULL);
	// glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	// glutInitWindowSize (500, 500);
	// glutInitWindowPosition (100, 100);
	// glutCreateWindow ("birds");
	// init2D(0.0,0.0,0.0);
	// // glutDisplayFunc(display);
	// glutMainLoop();
}

// void init2D(float r, float g, float b)
// {
// 	glClearColor(r,g,b,0.0);  
// 	glMatrixMode (GL_PROJECTION);
// 	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
// }

// void display(void)
// {
// 	// position p;
// 	// glClear(GL_COLOR_BUFFER_BIT);
// 	// glColor3f(1.0, 0.0, 0.0);

// 	// glBegin(GL_POINTS);
// 	// for(int i = 0; i < 10; i++)
// 	// {
// 	// 	// p = murmuration[i].pos_new;
// 	// 	glVertex2i(i*100.0,i*100.0);
// 	// }
// 	// glEnd();

// 	// glFlush();
// }

void environment::display_energy(void){
	
	float max = 0, min = 0, avg = 0;
	for(int i = 0; i<num; i++)
	{
		float E;
		E = murmuration[i].E_mech_old;
		if(E > max) max = E;
		if(E < min) min = E;
		avg += E;
	}

	cout<<"Maximum Energy at present instant is : " << max << "\n";
	cout<<"Minimum Energy at present instant is : " << min << "\n";
	cout<<"Average Energy at present instant is : " << avg/num << "\n";
}
