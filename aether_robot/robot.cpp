/*
 * robot.cpp
 * Arduino robot vehicle methods
 * Adapted from author: Miguel Grinberg (Michelino robot)
 * http://bit.ly/2iQXvlL
 */
#include "robot.h"

#define LOGGING  // comment out to disable logging.
#include "logging.h"

Aether::Robot::Robot()
          //initialiser list
      :leftMotor(LEFT_MOTOR_INIT), rightMotor(RIGHT_MOTOR_INIT),
      distanceSensor(I2CADDRESS, max_distance), /*,
      distanceAverage(max_distance)*/
      max_distance(TOO_CLOSE*10),
      run_time(30),
      encoder(R_ENCODER, L_ENCODER, &leftMotor, &rightMotor, TICKS_PER_180)
    {
      
    }

//---------------Public methods------------------------
void Aether::Robot::initialise()
{
 endTime = millis() + run_time * 1000;
 move();
}
//------------------------------------------------    
void Aether::Robot::run()
    /*
     * Update the state of the robot based on input from the sensors.
     * Must be called repeadtedly from loop
     */
    {
      unsigned long currentTime = millis();
      //stop();
      //delay(5000);
      //encoder.turnDegrees(180, 100, RIGHT);
      //while(true){Serial.println("STOP!");}
      /*
      if (stopped())
        return;
        
      unsigned long currentTime = millis();
      unsigned char *distance = distanceSensor.readDistance();

      //------LOGGING------
        log("distance: ");
        for(int i = 0; distance[i]; i++) {
          log("%u ", (int)distance[i]);
        }
        log("\n"); 
        log("state: %d, currentTime: %ul\n", state, currentTime);
        //log("min dir:  %u\n", distanceSensor.dir_min);
        //-------------------
        
      if (doneRunning(currentTime))
        stop();
      else if (moving()) {
        if (obstacleAhead(distance[1])); // use mid sensor distance
          turn(currentTime);
      }
      else if (turning()) {
         Serial.println("turning");
         if (doneTurning(currentTime, distance[1]))
          move();
        }
      */
      
      encoder.getCalcSpeed(currentTime); // takes arg of currentTime defined above by millis
      int calcSpeed = encoder.calcSpeed;
      Serial.println((int)calcSpeed);
      
     
      /*
      if (state == stateMoving) {
        unsigned char *distance = distanceSensor.readDistance();
        /*
        int dist_left = (int)distance[0];
        int dist_mid = (int)distance[1];
        int dist_right = (int)distance[2];
        */
        /*
        //------LOGGING------
        log("distance: ");
        for(int i = 0; distance[i]; i++) {
        log("%u ", (int)distance[i]);
        }
        log("\n"); 
        log("min dir:  %u\n", distanceSensor.dir_min);
        //-------------------
        */
      /*  if (distance[1] <= TOO_CLOSE) {
          
          stop();
        }
        
      }*/
    }

    //---------------Protected methods------------------------
    bool Aether::Robot::moving() { return (state == stateMoving); }
    bool Aether::Robot::turning() { return (state == stateTurning); }
    bool Aether::Robot::stopped() { return (state == stateStopped); }

//------------------------------------------------
  void Aether::Robot::move()
      {
        leftMotor.setSpeed(100);
        rightMotor.setSpeed(100);
        state = stateMoving;
      }
//------------------------------------------------
      void Aether::Robot::stop()
      {
        leftMotor.setSpeed(0);
        rightMotor.setSpeed(0);
        state = stateStopped;
      }
//------------------------------------------------
      bool Aether::Robot::doneRunning(unsigned long currentTime)
      {
        return (currentTime >= endTime);
      }
//------------------------------------------------
      bool Aether::Robot::obstacleAhead(unsigned char *distance) // takes value from middle sensor
      {
        return(distance <= TOO_CLOSE);
      }
//------------------------------------------------
      //turn left function
      //turn right function
      bool Aether::Robot::turn(unsigned long currentTime)
      {
        if (random(2) == 0) {   // decides to turn left or right based on random(2)
          leftMotor.setSpeed(-150); // turn in one direction
          rightMotor.setSpeed(150);
        }
        else {
          leftMotor.setSpeed(150); // turn opposite way
          rightMotor.setSpeed(-150);
        }
        state = stateTurning;
        endStateTime = currentTime + random(500, 1000);
      }
//------------------------------------------------
      bool Aether::Robot::doneTurning(unsigned long currentTime, unsigned char *distance)
      //to evaluate to true, time for turn must have passed, distance sensor must not see any obstacles ahead.
      {
        if (currentTime >= endStateTime)
          return(distance > TOO_CLOSE);
        return false;
      } 
       
