/**
l293d_motor_driver.h
L293D H bridge to drive motors for Aether robot
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2iQXvlL
*/

#include "motor_driver.h"

namespace Aether
{

	class Motor: public MotorDriver
	// class Motor derives from class MotorDriver
	{
  //Class member variables
  private:
  int motorEnable;
  int controlF;
  int controlB;
  int currentSpeed;
  
	public:
		//Class constructor method to set initial state of object.
		Motor(int ePin, int fPin, int bPin)
			: MotorDriver(), currentSpeed(0), motorEnable(ePin), controlF(fPin), controlB(bPin) // initialiser list
              
		{
     pinMode(motorEnable, OUTPUT);
     pinMode(controlF, OUTPUT);
     pinMode(controlB, OUTPUT);
		}

		void setSpeed(int speed)
		{
			currentSpeed = speed;
			if(speed > 0)
			{
				//set speed pins to currentSpeed
        analogWrite(motorEnable, currentSpeed);
				
				//set direction forwards
				digitalWrite(controlF, HIGH);
				digitalWrite(controlB, LOW);

			}
			else if (speed < 0) 
			{
				//set speed pins to currentSpeed
        analogWrite(motorEnable, -currentSpeed);
				
				//set direction backwards
				digitalWrite(controlF, LOW);
				digitalWrite(controlB, HIGH);

			}
			else
			{
				//stop
				digitalWrite(motorEnable, LOW);
			}
		}

		int getSpeed() const
		{
			return currentSpeed;
		}
		

	};

};
