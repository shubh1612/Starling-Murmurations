#include <vector>
#include "physics.hpp"
#include <cmath>

using namespace std;

static float NIEGHBOUR_RADIUS = 100.0; // constant
static float EPSILON_COHESION = 0.01; // constant
static float EPSILON_SEPARATION = -0.01; // constant
static float EPSILON_ALIGNMENT = 0.01; // constant
static float MASS_STARLING = 1; // constant
static float EPSILON_V = 0.01;

position::position(void){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

//Position
position position::operator+(const position &param){
	position temp;
	temp.x = x + param.x;
	temp.y = y + param.y;
	temp.z = z + param.z;
	return temp;
}

position position::operator-(const position &param){
	position temp;
	temp.x = x - param.x;
	temp.y = y - param.y;
	temp.z = z - param.z;
	return temp;
}

position position::operator/(const float &c){
	position temp;
	temp.x = x/c;
	temp.y = y/c;
	temp.z = z/c;
	return temp;
}

position position::operator*(const float &c){
	position temp;
	temp.x = x*c;
	temp.y = y*c;
	temp.z = z*c;
	return temp;
}

velocity::velocity(void){
	v_x = 0.0;
	v_y = 0.0;
	v_z = 0.0;
}

//Velocity
velocity velocity::operator+(const velocity &param){
	velocity temp;
	temp.v_x = v_x + param.v_x;
	temp.v_y = v_y + param.v_y;
	temp.v_z = v_z + param.v_z;
	return temp;
}

velocity velocity::operator-(const velocity &param){
	velocity temp;
	temp.v_x = v_x - param.v_x;
	temp.v_y = v_y - param.v_y;
	temp.v_z = v_z - param.v_z;
	return temp;
}

velocity velocity::operator/(const float &c){
	velocity temp;
	temp.v_x = v_x/c;
	temp.v_y = v_y/c;
	temp.v_z = v_z/c;
	return temp;
}

velocity velocity::operator*(const float &c){
	velocity temp;
	temp.v_x = v_x*c;
	temp.v_y = v_y*c;
	temp.v_z = v_z*c;
	return temp;
}
//Starling
void starling::get_neighbours(vector<starling> &murmuration){
	int star_num = murmuration.size(); 

	for(int i=0;i<star_num;i++)
	{	
		murmuration[i].neighbours.clear();
		murmuration[i].pos_old = murmuration[i].pos_new;
		murmuration[i].v_old = murmuration[i].v_new;
	}

	for(int i=0;i<star_num;i++)
	{
		position p1, p2;
		p1 = murmuration[i].pos_old;
		for(int j=i+1;j<star_num;j++)
		{
			p2 = murmuration[j].pos_old;
			float dist;
			dist = pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2) + pow((p1.z - p2.z), 2);
			if(dist < NIEGHBOUR_RADIUS)
			{
				murmuration[i].neighbours.push_back(j);
				murmuration[j].neighbours.push_back(i);
			}
		}
	}

}

velocity starling::cohesion_update(vector<starling> &murmuration){
	position cm;
	for(int i = 0; i < neighbours.size(); i++){
		cm = cm + murmuration[neighbours[i]].pos_old;
	}
	cm = cm/float(neighbours.size());

	velocity delta_v;

	position dir_vec = (cm - pos_old) * EPSILON_COHESION;

	delta_v.v_x = dir_vec.x;
	delta_v.v_y = dir_vec.y;
	delta_v.v_z = dir_vec.z;

	return delta_v;
}

velocity starling::separation_update(vector<starling> &murmuration){
	position sep;
	for(int i = 0; i < neighbours.size(); i++){
		sep = sep + murmuration[neighbours[i]].pos_old - pos_old;
	}

	velocity delta_v;

	position dir_vec = sep * EPSILON_SEPARATION;

	delta_v.v_x = dir_vec.x;
	delta_v.v_y = dir_vec.y;
	delta_v.v_z = dir_vec.z;

	return delta_v;
}

velocity starling::alignment_update(vector<starling> &murmuration){
	velocity dsum;
	for(int i = 0; i < neighbours.size(); i++){
		dsum = dsum + murmuration[neighbours[i]].v_old - v_old;
	}

	velocity delta_v;

	delta_v = dsum*EPSILON_ALIGNMENT;

	return delta_v;
}

void starling::update_velocity(vector<starling> &murmuration){
	v_new = v_old + alignment_update(murmuration) + separation_update(murmuration) + cohesion_update(murmuration);
}

void starling::update_position(float time_step){
	pos_new.x = pos_old.x + v_new.v_x*time_step;
	pos_new.y = pos_old.y + v_new.v_y*time_step;
	pos_new.z = pos_old.z + v_new.v_z*time_step;
}

void starling::update_stored_energy(void){
	float mod_v;
	E_mech_old = E_mech_new;
	E_str_old = E_str_new;

	mod_v = pow(v_new.v_x, 2) + pow(v_new.v_y, 2) + pow(v_new.v_z, 2);
	E_mech_new = 0.5 * MASS_STARLING * mod_v + MASS_STARLING * 9.8 * abs(pos_new.z);
	
	velocity mod_change;
	mod_change = v_new - v_old;
	float vm = abs(mod_change.v_x) + abs(mod_change.v_y) + abs(mod_change.v_z);

	E_str_new -= E_mech_new - E_mech_old - EPSILON_V * vm;
}

void starling::update_velocity_from_energy(void){

}
