#include <vector>
#include "simulation.hpp"
#include <stdlib.h>

using namespace std;


void environment::init_environment(void){
	
	cout<<"Enter number of birds to simulate: \n";
	cin>>num;
	cout<<"Simulation has started.....\n";
	
	for(int i=0;i<num;i++)
	{
		starling c;
		position p;
		velocity v;

		/***Initializing position, velocity and energy***/
		p.x = p.y = i/100;
		p.z = 10;

		v.v_x = v.v_y = v.v_z = (i+1)/100;

		c.E_mech_old = 100000; /**some value **/
		c.pos_new = p;
		c.v_new = v;

		murmuration.push_back(c);
	}
}

void environment::update(void){

}

void environment::handle_intersection(void){

}

void environment::simulate(void){

}

void environment::display_energy(void){
	
	float max = 0, min = 0, avg = 0;
	for(int i = 0; i<num; i++)
	{
		float E, avg_vel;
		E = murmuration[i].E_mech_old;
		if(E > max) max = E;
		if(E < min) min = E;
		avg += E;
	}

	cout<<"Maximum Energy at present instant is - "<<max<<"\n";
	cout<<"Minimum Energy at present instant is - "<<min<<"\n";
	cout<<"Average Energy at present instant is - "<<avg<<"\n";
}