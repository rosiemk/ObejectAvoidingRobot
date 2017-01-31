/*
*   i2c_distance_sensor.h
*   Distance sensor definition for the Aether robot
*   3 ultrasonic sensors connected via I2C bus and ATTiny 85.
*   Slave programme for ATtiny85 is: newslave_3sensors_attiny85_21dec.ino
*   Adapted from: Miguel Grinberg (Michelino robot)
*   Miguel Grinberg - Michelino robot - http://bit.ly/2kkeHwu
*   Andreas Spiess - https://www.youtube.com/watch?v=vj0SUYo8f_A
*/
#pragma once
//#include "distance_sensor.h"
#include <Arduino.h>
#include <Wire.h>


namespace Aether
{
    class DistanceSensor //: public DistanceSensorDriver
    {    
      private:
        int sensor;
        int place;
        unsigned char distance[3];
        //int dir_min;
        //int dist_min = 0;
        const int _left = 0; // constants definded in h file not cpp
        const int _middle = 1;
        const int _right = 2;
        int I2CAddress;

        //private method 
        unsigned char readTiny(int address);
      
      public:
        DistanceSensor(int i2c, int maxDistance);

        //int dir_min;
        int dist_min; 

        enum direction_m {left, middle, right};
        direction_m dir_min; // refers to enum
        
        unsigned char* readDistance();
        void getDistance();
   
    };

};
