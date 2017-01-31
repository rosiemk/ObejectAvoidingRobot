/**
l293d_motor_driver.h
L293D H bridge to drive motors for Aether robot
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2iQXvlL
*/
#pragma once
//#include "motor_driver.h"
#include <Arduino.h>

namespace Aether
{

	class Motor//: public MotorDriver
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
		Motor(int ePin, int fPin, int bPin);
              
		void setSpeed(int speed);
    int getSpeed() const;

	};

};
