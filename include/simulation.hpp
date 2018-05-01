#include <vector>

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

/*! \brief Datatype to the murmuration simulation data at a timestep*/ 
class environment{
public:
	/// Number of starlings in the simulation
	int num;

	/// List of starlings in the simulation
	std::vector<starling> murmuration;

	/// Time interval after which each calculation is performed and murmuration displayed
	float time_step;

	/** Initializes the initial position, velocity and energy of starlings in space
	*	Rule for initialization defined in mathematical model
	*/
	void init_environment(void);

	/** Update state of the environment i.e position, velocity and energy of all starlings
	*/
	void update(void);

	/** Finds intersections between intersections and handle them as per requirement
	*/
	void handle_intersection(void);

	/** Display the position and velocity vectors of all the starlings in 3D space
	*/
	void simulate(void);

	/** Display the energy of each boid on commandline
	*/
	void display_energy(void);

};


#endif