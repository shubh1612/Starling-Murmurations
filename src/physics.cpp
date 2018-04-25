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

}

void starling::update_velocity_from_energy(void);{

}
