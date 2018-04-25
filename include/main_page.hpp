/*!	\mainpage Documentation
*	
*	\section intro_sec Introduction
*	
*	This is a basic model to simulate murmuration of starlings. Discrete time simulation is being performed to model the behaviour. 
*	
*	Basic rules followed by a flock are:
*		- Separation - avoid crowding neighbors (short range repulsion)
*		- Alignment - steer towards average heading of neighbors
*		- Cohesion - steer towards average position of neighbors (long range attraction)
*	
*	All the birds are initially given some initial position, velocity and energy in 3D space.
*	Based on the three base rules and energy consideraton, the parameters are updated at each time step and displayed on screen.
*	 
*	\section code_sec Code Structure
*	
*	documentation/ - contains the documentation for the code 
*	
*	include/ - contains the header files
*	
*	mathematical_model/ - contains the details of physical modelling
*	
*	src/ - contains the source files
*	
*	UML_diagrams/ - contains the functional specification and class diagram for the model
*	
*	useful_links - contains references for the model
*	
*	There are two C++ header files that provide utilities for simulation of model:
*		- physics.hpp - provide various classes for entities that are involved in the physics of simulation
*		- simulation.hpp - provide an environment object to set various hyperparameters of the simulation
*	 
*	 
*/