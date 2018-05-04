#include <vector>
#include "physics.hpp"
#include <cmath>

using namespace std;

// static float NEIGHBOUR_RADIUS = 10.0; // constant
// static float EPSILON_COHESION = 0.5; // constant
// static float EPSILON_SEPARATION = -0.072; // constant
// static float EPSILON_ALIGNMENT = 0.01; // constant
// static float MASS_STARLING = 10; // constant
// static float EPSILON_V = 1;
// static float EPSILON_CLOSE = 0.01;

static float NEIGHBOUR_RADIUS = 10.0; // constant
static float EPSILON_COHESION = 0.0133; // constant
static float EPSILON_SEPARATION = -15000; // constant
static float EPSILON_ALIGNMENT = 0.125; // constant
static float MASS_STARLING = 10; // constant
static float EPSILON_V = 1;
static float EPSILON_CLOSE = 900;
static float SPEED_LIMIT = 800;
static float X_LIMIT = 100;
static float Y_LIMIT = 100;
static float Z_LIMIT = 100;
static float WALL_FORCE = 30;

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
	#pragma omp parallel for num_threads(4)
	for(int i=0;i<star_num;i++)
	{	
		murmuration[i].neighbours.clear();
		murmuration[i].pos_old = murmuration[i].pos_new;
		murmuration[i].v_old = murmuration[i].v_new;
		murmuration[i].neighbours.resize(7);

		int count = 0;
		position p1, p2;
		p1 = murmuration[i].pos_old;

		for(int j=0;j<star_num;j++){
			if (count > 7){
				break;
			}
			if(i==j) continue;

			p2 = murmuration[j].pos_old;
			float dist;
			dist = pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2) + pow((p1.z - p2.z), 2);
			if(dist < NEIGHBOUR_RADIUS)
			{	
				murmuration[i].neighbours[count] = j;
				count++;
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
		position p = murmuration[neighbours[i]].pos_old;
		if((pow(p.x - pos_old.x, 2) + pow(p.y - pos_old.y, 2) + pow(p.z - pos_old.z, 2)) < EPSILON_CLOSE)
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
		dsum = dsum + murmuration[neighbours[i]].v_old;
	}
	dsum = dsum/neighbours.size();

	velocity delta_v;

	delta_v = (dsum - v_old)*EPSILON_ALIGNMENT;

	return delta_v;
}

void starling::update_velocity(vector<starling> &murmuration){
	v_new = v_old + alignment_update(murmuration) + separation_update(murmuration) + cohesion_update(murmuration);
	if((pow(v_new.v_x, 2) + pow(v_new.v_y, 2) + pow(v_new.v_z, 2)) > SPEED_LIMIT)
		v_new = v_new/SPEED_LIMIT;
}

void starling::update_position(float time_step){
	pos_new.x = pos_old.x + v_new.v_x*time_step;
	pos_new.y = pos_old.y + v_new.v_y*time_step;
	pos_new.z = pos_old.z + v_new.v_z*time_step;

	if(pos_new.x > X_LIMIT)
		v_new.v_x = v_new.v_x - WALL_FORCE;
	if(pos_new.y > Y_LIMIT)
		v_new.v_y = v_new.v_y - WALL_FORCE;
	if(pos_new.z > Z_LIMIT)
		v_new.v_z = v_new.v_z - WALL_FORCE;
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

	float delta_E = 0;
	if(E_mech_new - E_mech_old > 0) 
		delta_E = E_mech_new - E_mech_old;
	
	E_str_new = E_str_new - delta_E - EPSILON_V * vm;
}

void starling::update_velocity_from_energy(void){

}
