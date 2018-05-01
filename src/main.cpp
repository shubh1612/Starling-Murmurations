#include <iostream>
#include "simulation.hpp"
#include "physics.hpp"

using namespace std;

static float TOTAL_TIME = 4.0;

int main(){
	
	environment env;
	int n; 
	cout << "Enter number of birds: ";
	cin >> n;
	cout << "\n";

	env.num = n;
	env.init_environment();

	float present_time = 0;

	while(present_time < TOTAL_TIME){
		env.update();
		env.handle_intersection();
		env.simulate();
		env.display_energy();

		present_time += env.time_step;
	}

	return 0;
}