/*
* wheel_encoder.cpp
* Counts revolutions of wheels to calculate speed, distance and degrees turned.
* Adapted from RobotC
* http://bit.ly/2kif0f2
*/

#include "wheel_encoder.h"
//---Global-----
 int rightCoder = 0;
 int leftCoder = 0;
 void rightCount()
 {
  rightCoder ++;
 }
 void leftCount()
 {
   leftCoder ++;
 }
//-------------

//namespace::class::constructor
Aether::WheelEncoder::WheelEncoder (int ePinL, int ePinR, Motor* lM, Motor* rM, int ticks180)
//initialiser list and variables, comma separated
  :encodePinL(ePinL),
   encodePinR(ePinR),
   ticksPer180(ticks180),
  
  wheelDiameter(7), //cm
  wheelCirc(2 * 3.142 * (wheelDiameter/2)), //cm
  gearTeeth(10),
  //ticksPer180(44); // number of ticks to turn 180 degrees
  tickConst((ticksPer180/180)*100), //constant to determine number of clicks per degree
  leftMotor(lM),
  rightMotor(rM),
  lastSpeed(0),
  calcSpeed(0),
  revPerSec(0),
  coderAverage(0)
  { 
  //attachInterrupt(digitalPinToInterrupt(encodePin), std::bind(&Aether::WheelEncoder::count, this), CHANGE);
  attachInterrupt(digitalPinToInterrupt(encodePinL), leftCount, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encodePinR), rightCount, CHANGE);
   
  }

//---------Public method ------------  

    int Aether::WheelEncoder::getCalcSpeed(unsigned long currentTime)
    {
      static unsigned long timer = 0;
      if (currentTime-timer > 100) {   
            
        coderAverage = (leftCoder + rightCoder)/2;
        revPerSec = (coderAverage*10)/gearTeeth;  // coder interrups in 100ms * 10(1s) encoder gear has 10 teeth per revolution
        calcSpeed = revPerSec * wheelCirc;         //cm/s
        lastSpeed = coderAverage; // record latest speed value
        leftCoder = 0;
        rightCoder = 0;
        timer = currentTime;
        //return calcSpeed;
      }
    }
//-----------------------------------
 
    void Aether::WheelEncoder::turnDegrees(int degrees, int turnSpeed, TURN_DIRECTION td)
    {
      
      leftCoder = 0;
      rightCoder = 0;
      coderAverage = (leftCoder + rightCoder)/2;
      //determine number of ticks to turn x number of degrees
      int tickGoal = (tickConst * degrees) /100;

      //Start point turn
      while((coderAverage)<tickGoal) {
        Serial.print(tickGoal);
        Serial.print(" ");
        Serial.println(coderAverage);
        if(td == LEFT)
        {
          leftMotor->setSpeed(-100);
         rightMotor->setSpeed(100);
        }
        else
        {
          leftMotor->setSpeed(100);
          rightMotor->setSpeed(-100);
        }
         
         coderAverage =  (leftCoder + rightCoder)/2;
        }
         leftMotor->setSpeed(0);
         rightMotor->setSpeed(0);
         
    }
//-----------Protected methods--------------

