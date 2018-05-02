#include <iostream>
#include "simulation.hpp"
#include "physics.hpp"
#include "omp.h"

using namespace std;

static float TOTAL_TIME = 40.0;

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
		double start = omp_get_wtime();
		env.update();
		env.handle_intersection();
		// env.simulate();
		env.display_energy();

		present_time += env.time_step;

		// cout << omp_get_wtime() - start << endl;
	}

	return 0;
}