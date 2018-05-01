#include <vector>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "omp.h"
#include "physics.hpp"
#include "simulation.hpp"

using namespace std;

static float E_INITIAL = 100000;
static float MEAN_XY = 200;  
static float MEAN_Z = 10;
static float VAR_POSXY = 50;
static float VAR_POSZ = 2;
static float MEAN_VEL = 5; 
static float VAR_VEL = 1; 
static float TIME_STEP = 3.0; 


void environment::init_environment(void){

	time_step = TIME_STEP;

	murmuration.resize(num);
	default_random_engine generator1, generator2, generator3;
	normal_distribution<float> distribution1(MEAN_XY, VAR_POSXY);
	normal_distribution<float> distribution2(MEAN_Z, VAR_POSZ);
	normal_distribution<float> distribution3(MEAN_VEL, VAR_VEL);

	#pragma omp for
	for(int i = 0; i < num; i++)
	{
		starling c;
		position p;
		velocity v;

		/***Initializing position, velocity and energy***/
		float number1 = distribution1(generator1);
		p.x = p.y = number1;
		float number2 = distribution2(generator2);
		p.z = number2;

		float number3 = distribution3(generator3);				
		v.v_x = v.v_y = v.v_z = number3;

		c.E_mech_old = E_INITIAL; /**some value **/
		c.pos_new = p;
		c.v_new = v;

		murmuration[i] = c;
	}
}

void environment::update(void){
	#pragma omp for
	for(int i = 0 ; i < num; i++){
		murmuration[i].get_neighbours(murmuration);
		murmuration[i].update_velocity(murmuration);
		murmuration[i].update_position(time_step);
		murmuration[i].update_stored_energy();
	}
}

void environment::handle_intersection(void){

}

void environment::simulate(void){

}

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

	cout<<"Maximum Energy at present instant is - " << max << "\n";
	cout<<"Minimum Energy at present instant is - " << min << "\n";
	cout<<"Average Energy at present instant is - " << avg/num << "\n";
}