#include <vector>


#ifndef PHYSICS_HPP
#define PHYSICS_HPP

/*! \brief Datatype to store position of a starling*/ 
class position{
public:
	/// x-coordinate
	float x;

	/// y-coordinate
	float y;

	/// z-coordinate
	float z;

	position operator+(const position &param);
};

/*! \brief Datatype to store velocity of a starling*/ 
class velocity{
public:
	/// Velocity in x-direction
	float v_x;
	
	/// Velocity in y-direction
	float v_y;

	/// Velocity in z-direction
	float v_z;

	velocity operator+(const velocity &param);
};

/*! \brief Datatype to store starling data*/ 
class starling{
public:
	/// Position of the starling at an instance
	position pos;

	/// Velocity of the starling at an instance
	velocity v;

	/// Index of neighbours of starling in starling list
	std::vector<int> neighbours;

	/// Mechanical energy of boid at the previous time_step
	float E_mech_old;

	/// Energy stored (muscle energy) with an starling at an instance
	float E_str;

	/** Finds the neighbours of the starling
	* @param[in] murmuration List of all starlings
	*/
	void get_neighbours(std::vector<starling> murmuration);

	/** Finds the velocity update from the "Cohesion" rule
	*   @return Change in velocity due to the rule 
	*/
	velocity cohesion_update(void);

	/** Finds the velocity update from the "Separation" rule
	*   @return Change in velocity due to the rule 
	*/
	velocity separation_update(void);

	/** Finds the velocity update from the "Alignment" rule
	*   @return Change in velocity due to the rule 
	*/
	velocity alignment_update(void);

	/** Update velocity using the three base rules
	*/
	void update_velocity(void);

	/** Update position based on the velocity at an instance
	*/
	void update_position(void);

	/** Update the energy stored(muscle energy) with the starling after change in velocity and position
	*	Update only performed if the energy stored is more than some specified limit
	*/
	void update_stored_energy(void);

	/** Update the velocity of based on energy stored
	*	If the stored energy is less than a specified constant, increase the stored energy by decreasing the mechanical energy at the present instance
	*/
	void update_velocity_from_energy(void);

};


#endif