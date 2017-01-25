/*
*	distance_sensor.h
* 	Distsance sensor definition for the Aether robot
* 	Adapted from author: Miguel Grinberg (Michelino robot)
*	http://bit.ly/2kkeHwu
*/

namespace Aether
{
	class DistanceSensorDriver //name of class
	{ //definition of class
	public:
		/*
		Class constructor
		distance is max distance (cm) that needs to be tracked.
		*/	
		DistanceSensorDriver(unsigned int distance) : maxDistance(distance) 
		{}

		/*
		Return the distance to the nearest obstacle (cm)
		or max distance if no object is detected
		*/
		virtual unsigned int readDistance() = 0;


	  protected: // private to outside but available to subclasses.
	  unsigned int maxDistance;	
	};
};
