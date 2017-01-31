/*
*   distance_sensor.cpp
*   Distance sensor methods for the Aether robot
*   3 ultrasonic sensors connected via I2C bus and ATTiny 85.
*   Slave programme for ATtiny85 is: newslave_3sensors_attiny85_21dec.ino
*   Adapted from: Miguel Grinberg (Michelino robot)
*   Miguel Grinberg - Michelino robot - http://bit.ly/2kkeHwu
*   Andreas Spiess - https://www.youtube.com/watch?v=vj0SUYo8f_A
*/

#include "i2c_distance_sensor.h"

//namespace::class::constructor
Aether::DistanceSensor::DistanceSensor(int i2c, int maxDistance)
 //initialiser list and variables, comma separated
        : sensor(maxDistance), I2CAddress(i2c),
        //int dir_min(0),
        dist_min(0)
        {
        }

//--------private method---------
 unsigned char Aether::DistanceSensor::readTiny(int address)
   {
     unsigned char hh ;
     long entry = millis();
     Wire.requestFrom(address, 1);
     while (Wire.available() == 0 && (millis() - entry) < 100) Serial.print("W");
     if (millis() - entry < 100) hh = Wire.read();
     return hh;
   }
         
//--------public method---------
unsigned char* Aether::DistanceSensor::readDistance()
   {         
            while(readTiny(I2CAddress)<255) {
            //Serial.print("WT");
          }
            for (place = 0; place < 3; place++) {
            distance[place] = readTiny(I2CAddress);
          }            
           
          //return maxDistance;
         if (distance[_left] < distance[_middle] && distance[_left] < distance[_right])
         {
          dist_min = distance[_left];
          dir_min = left; 
         }
         else {
          if (distance[_middle] < distance[_right])
          {
           dist_min = distance[_middle];
           dir_min = middle;
          }
          else {
            dist_min = distance[_right];
            dir_min = right;
          }
         }
                  
           delay(10);
           return distance;
    }
