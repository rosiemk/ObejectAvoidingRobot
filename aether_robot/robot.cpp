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
      encoder(R_ENCODER, L_ENCODER, &leftMotor, &rightMotor/*, TICKS_PER_180*/),
      dataString("p"),
      serial(RECEIVE, TRANSMIT)
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

      
      /*
      encoder.getCalcSpeed(currentTime); // takes arg of currentTime defined above by millis
      int calcSpeed = encoder.calcSpeed;
      Serial.println((int)calcSpeed);
      */
     
      unsigned long currentTime = millis();
      unsigned char *distance = distanceSensor.readDistance();
      /*
      if(moving())
      {
        if (obstacleAhead(distance[_RIGHT]))
        {
          stop();

      }
      */
      
      int calcDistance = encoder.getDistance();
      String getData = getDataString(); //return value of getDataString
      
      
      if (stopped()) {
        return;
      }
      
      if (moving()) {
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
       
        //if(distanceSensor.dir_min == middle)
       if (distanceSensor.dir_min == _MIDDLE && obstacleAhead(distance[_MIDDLE])) {
           calcDistance;
           //log("calc distance: %u\n", calcDistance);
           
           getData;
           serial.sendData(getData);
           Serial.println(getData);
           
          if (random(2) == 0) {
            encoder.turnDegrees(90,TURN_SPEED,RIGHT);
            
          }
          else {
            encoder.turnDegrees(90, TURN_SPEED, LEFT);
          }
          //log("bearing: %u\n", encoder.bearing);
       }  
       if (distanceSensor.dir_min == _LEFT && obstacleAhead(distance[_LEFT])) {
          calcDistance;
          //log("calc distance: %u\n", calcDistance);
          
           getData;
           serial.sendData(getData);
           Serial.println(getData);
           
          encoder.turnDegrees(45,TURN_SPEED,RIGHT);
          //log("bearing: %u\n", encoder.bearing);     
            }
       else if (distanceSensor.dir_min == _RIGHT && obstacleAhead(distance[_RIGHT])) {
          calcDistance;
          //log("calc distance: %u\n", calcDistance);
          
           getData;
           serial.sendData(getData);
           Serial.println(getData);
           
          encoder.turnDegrees(45,TURN_SPEED,LEFT);
          //log("bearing: %u\n", encoder.bearing);
          
        }
        
       else {
        move(); 
       }
      }
      
    }

    //---------------Protected methods------------------------
    bool Aether::Robot::moving() { return (state == stateMoving); }
    bool Aether::Robot::turning() { return (state == stateTurning); }
    bool Aether::Robot::stopped() { return (state == stateStopped); }

//------------------------------------------------
  void Aether::Robot::move()
      {
        leftMotor.setSpeed(SPEED);
        rightMotor.setSpeed(SPEED);
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
      void Aether::Robot::pause(unsigned long currentTime)
      {
        //timed 1000ms pause
        leftMotor.setSpeed(0);
        rightMotor.setSpeed(0);
        endStateTime = currentTime + 1000;
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
      bool Aether::Robot::turn(unsigned long currentTime)
      {
        
        if (random(2) == 0) {   // decides to turn left or right based on random(2)
          leftMotor.setSpeed(-TURN_SPEED); // turn in one direction
          rightMotor.setSpeed(TURN_SPEED);
        }
        else {
          leftMotor.setSpeed(TURN_SPEED); // turn opposite way
          rightMotor.setSpeed(-TURN_SPEED);
        }
        state = stateTurning;
        endStateTime = currentTime + random(500, 1000);
      }
//------------------------------------------------
      bool Aether::Robot::doneTurning(unsigned char *distance)
      //to evaluate to true, time for turn must have passed, distance sensor must not see any obstacles ahead.
      {
        //if (currentTime >= endStateTime)
        if(distance > TOO_CLOSE) {
        return false;
        }
      }
//------------------------------------------------
      bool Aether::Robot::needToTurn(unsigned char *distance)
      {
        if (distance <= TOO_CLOSE) {
          return true;
          }
      }
//-------------------------------------------------
String Aether::Robot::getDataString()
      {
      dataString = "<p";
      dataString += encoder.getDistance();
      dataString += ",";
      dataString += encoder.bearing;
      dataString += ">";
      //Serial.println(dataString);

      return dataString;
      }

