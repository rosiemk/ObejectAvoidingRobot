/**
aether_robot.ino
Arduino robot vehicle firmware
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2iQXvlL
*/
#include <NewPing.h>
#include <Wire.h>
#include <avr/wdt.h> // watchdog
#include "i2c_distance_sensor.h"

#include "l293d_motor_driver.h"
#define LEFT_MOTOR_INIT 11, 12, 13
#define RIGHT_MOTOR_INIT 5, 9, 8

int too_close = 10;
int max_distance = too_close*20;
const int I2CAddress = 8;




namespace Aether
{
  class Robot // methods initialise() and run()
  {
    public:
    //Class constructor
    Robot()
      //initialiser list
      :leftMotor(LEFT_MOTOR_INIT), rightMotor(RIGHT_MOTOR_INIT),
      distanceSensor(I2CAddress, max_distance)
    {
      initialise();
    }

    //Initialise the robot state
    void initialise()
    {
      leftMotor.setSpeed(255);
      rightMotor.setSpeed(255);
      state = stateRunning;
    }

    /*
     * Update the state of the robot based on input from the sensors.
     * Must be called repeadtedly
     */
    void run()
    {
     //distanceSensor.readDistance();

      if (state == stateRunning) {
        if (distanceSensor.readDistance() <= too_close) {
          state = stateStopped;
          leftMotor.setSpeed(0);
          rightMotor.setSpeed(0);
        }
      }
      
    }

    private:
      Motor leftMotor;
      Motor rightMotor;
      DistanceSensor distanceSensor;
      
      enum state_t { stateStopped, stateRunning }; //enum holds user defined variables
      state_t state;
  };
};

Aether::Robot robot;

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    wdt_disable();
    robot.initialise();
}

void loop()
{
    wdt_enable(WDTO_1S);
    robot.run();
    wdt_reset();
}
