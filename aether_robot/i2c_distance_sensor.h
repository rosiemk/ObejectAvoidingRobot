/*
*   distance_sensor.h
*   Distance sensor definition for the Aether robot
*   3 ultrasonic sensors connected via I2C bus and ATTiny 85.
*   Slave programme for ATtiny85 is: newslave_3sensors_attiny85_21dec.ino
*   Adapted from: Miguel Grinberg (Michelino robot)
*   Miguel Grinberg - Michelino robot - http://bit.ly/2kkeHwu
*   Andreas Spiess - https://www.youtube.com/watch?v=vj0SUYo8f_A
*/

#include "distance_sensor.h"

namespace Aether
{
    class DistanceSensor : public DistanceSensorDriver
    {    
      public:
        DistanceSensor(int i2c, int maxDistance)
        //initialiser list
            : DistanceSensorDriver(maxDistance), 
              sensor(maxDistance), I2CAddress(i2c)
        {
        //int dir_min;
        //int dist_min;
        }
        unsigned int readDistance();
        unsigned int getMinDistance();

       private:
        int sensor;
        int place;
        //byte distance[3];
        //int dir_min;
        //int dist_min = 0;
        const int left = 0;
        const int middle = 1;
        const int right = 2;
        int I2CAddress;

        //private method 
        byte readTiny(int address);
        
    };

    struct ProximityData { // store values to be returned in readDistance() function.
      byte distance[3];
      int dir_min;
      int dist_min;
    };
    
 //--------private method---------
 byte DistanceSensor::readTiny(int address)
   {
     byte hh ;
     long entry = millis();
     Wire.requestFrom(address, 1);
     while (Wire.available() == 0 && (millis() - entry) < 100) Serial.print("W");
     if (millis() - entry < 100) hh = Wire.read();
     return hh;
   }
         
//--------public method---------
unsigned int DistanceSensor::readDistance()
   {
            ProximityData pData;
            ProximityData *pd = &pData; //pointer pd to Proximity Data structure
            
            while(readTiny(I2CAddress)<255) {
            Serial.print("WT");
          }
            for (place = 0; place < 3; place++) {
            pd->distance[place] = readTiny(I2CAddress);
            return pd->distance[place];
            
            //Serial.print(pd->distance[place]);
            //Serial.print(" ");
          }
         
            //Serial.println();
         
          //return maxDistance;
         if (pd->distance[left] < pd->distance[middle] && pd->distance[left] < pd->distance[right])
         {
          pd->dist_min = pd->distance[left];
          pd->dir_min = left; 
         }
         else {
          if (pd->distance[middle] < pd->distance[right])
          {
           pd->dist_min = pd->distance[middle];
           pd->dir_min = middle;
          }
          else {
            pd->dist_min = pd->distance[right];
            pd->dir_min = right;
          }
         }
         return pd;
         
         /*
          * Serial.print(pd->dist_min);
         Serial.print(" ");
         Serial.println(pd->dir_min);
         */ 
           delay(10);
           
    }

         
};
