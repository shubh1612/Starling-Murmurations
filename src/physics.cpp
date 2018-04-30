#include <vector>
#include "physics.hpp"

using namespace std;

//Position
position position::operator+(const position &param){
	position temp;
	temp.x = x + param.x;
	temp.y = y + param.y;
	temp.z = z + param.z;
	return temp;
}

//Velocity
velocity velocity::operator+(const velocity &param){
	velocity temp;
	temp.v_x = v_x + param.v_x;
	temp.v_y = v_y + param.v_y;
	temp.v_z = v_z + param.v_z;
	return temp;
}

//Starling
void starling::get_neighbours(vector<starling> murmuration){
	for(int i=0;i<num;i++)
	{
		murmuration[i].pos_old = murmuration[i].pos_new;
		murmuration[i].v_old = murmuration[i].v_new;
	}

	for(int i=0;i<num;i++)
	{
		position p1, p2;
		p1 = murmuration[i].pos_old;
		for(int j=i+1;j<num;j++)
		{
			p2 = murmuration[j].pos_old;
			float dist;
			dist = pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2) + pow((p1.z - p2.z), 2);
			if(dist < min_dist)
			{
				murmuration[i].neighbours.push_back(j);
				murmuration[j].neighbours.push_back(i);
			}
		}
	}

}

velocity starling::cohesion_update(void){
	
}

velocity starling::separation_update(void){

}

velocity starling::alignment_update(void){

}

void starling::update_velocity(void){

}

void starling::update_position(void){

}

void starling::update_stored_energy(void);{
	
	float E;
	velocity total_v;
	total_v = pow(v_new.v_x, 2) + pow(v_new.v_y, 2) + pow(v_new.v_z, 2);
	E = 0.5*m*total_v + m*9.8*abs(pos_new.z);
	if(E - E_mech_old > 0) E_str -= E - E_mech_old;
	E_mech_old = E;
}

void starling::update_velocity_from_energy(void);{

}
