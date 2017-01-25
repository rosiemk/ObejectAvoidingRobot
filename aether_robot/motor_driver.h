/*
motor_driver.h
Motor driver definition for Aether robot
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2iQXvlL
*/

namespace Aether 
{
	//groups definitions under name Aether

	class MotorDriver //methods setSpeed and getSpeed
	{
	public:
		/**
		Change speed of motor
		Values -255 to 255.
		+ve forward, -ve backwards. 0 to stop.
		*/

		virtual void setSpeed(int speed) = 0;
		//virtual can be overwritten by subclass

		
		//Return current speed of motor  with range -255 to 255
		virtual int getSpeed() const = 0;
		//const does not change internal state of object.
	};

};
