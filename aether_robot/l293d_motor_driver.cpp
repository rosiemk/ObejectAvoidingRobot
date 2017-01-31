/**
l293d_motor_driver.cpp
L293D H bridge to drive motors for Aether robot
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2iQXvlL
*/

#include "l293d_motor_driver.h"

//namespace::class::constructor
Aether::Motor::Motor(int ePin, int fPin, int bPin)
//initialiser list and variables, comma separated
: /*MotorDriver(), */currentSpeed(0), motorEnable(ePin), controlF(fPin), controlB(bPin)

    {
     pinMode(motorEnable, OUTPUT);
     pinMode(controlF, OUTPUT);
     pinMode(controlB, OUTPUT);
    }

// ----------Public methods--------------------
    void Aether::Motor::setSpeed(int speed)
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
// ------------------------------------------
    int Aether::Motor::getSpeed() const
    {
      return currentSpeed;
    }
