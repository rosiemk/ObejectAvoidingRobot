/*
 * robot.h
 * Arduino robot vehicle definition
 * Adapted from author: Miguel Grinberg (Michelino robot)
 * http://bit.ly/2iQXvlL
 */

#pragma once
//#define LOGGING  // comment out to disable logging.
#include "i2c_distance_sensor.h"
#define TOO_CLOSE 20
#define I2CADDRESS 8

#include <Arduino.h>
#include "moving_average.h"

#include "l293d_motor_driver.h"
#define LEFT_MOTOR_INIT 11, 12, 13
#define RIGHT_MOTOR_INIT 5, 9, 8

#include "wheel_encoder.h"
#define R_ENCODER 2
#define L_ENCODER 3
#define TICKS_PER_180 31

namespace Aether
{
  class Robot // methods initialise() and run()
  {
    public:
    //Class constructor
    Robot();

    void initialise();
    void run();
   
    protected:
      bool moving();
      bool turning();
      bool stopped();
      void move();
      void stop();
      bool doneRunning(unsigned long currentTime);
      bool obstacleAhead(unsigned char *distance);
      bool turn(unsigned long currentTime);
      bool doneTurning(unsigned long currentTime, unsigned char *distance);
         
    private:
      int max_distance;
      int run_time; //used in initialise method
      Motor leftMotor;
      Motor rightMotor;
      DistanceSensor distanceSensor;
      unsigned long endStateTime; // for timed action
      unsigned long endTime;
      //MovingAverage<unsigned char, 3> distanceAverage;
      WheelEncoder encoder;  // encoder object
      
      enum state_t { stateStopped, stateMoving, stateTurning }; //enum holds user defined variables
      state_t state;

      
  };
  
};
