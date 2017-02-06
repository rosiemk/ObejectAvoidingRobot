/*
* wheel_encoder.h
* Counts revolutions of wheels to calculate speed, distance and degrees turned.
* Adapted from RobotC
* http://bit.ly/2kif0f2
*/
#pragma once 
#include <Arduino.h>
#include "l293d_motor_driver.h"

namespace Aether
{
  enum TURN_DIRECTION
  {
    LEFT,
    RIGHT
  };
  
  class WheelEncoder
  {
  private:
  
  int encodePinL;
  int encodePinR;
  int wheelDiameter; //cm
  float wheelCirc; //cm
  int gearTeeth;
  float ticksPer180; // number of ticks to turn 180 degrees
  float tickConst; //CALCULATE MANUALLY (ticksPer180/180)*100 > constant to determine number of clicks per degree
  //int coder;  // counter for encoder ticks
  int lastSpeed;
  //int calcSpeed;
  int revPerSec;
  Motor *leftMotor; //holds address to motor object
  Motor *rightMotor;
  int coderAverage;
  

  // private methods
  
  public:
    WheelEncoder (int ePinL, int ePinR, Motor *lM, Motor *rM, int ticks180 = 44); // pointers to leftMotor and rightMotor, default ticks180 goes at end

    int calcSpeed;
    int bearing;
    int calcDistance;
    // public methods
    //void count(); // static belongs to class rather than instance.
    void getCalcSpeed(unsigned long currentTime);
    void turnDegrees(int degrees, int turnSpeed, TURN_DIRECTION td);
    void getBearing(int degrees, TURN_DIRECTION td);
    int getDistance();
    
  };

};

