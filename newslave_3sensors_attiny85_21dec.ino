

/*
This sketch runs on an ATtiny85 connected to an Arduino uno running a receiver sketch
This sketch gets distance data from three ultrasonic sensors and transmits it to the Arduino when requested
Andreas Spiess, 2015
*/

#include <TinyWireS.h>       // Requires fork by Rambo with onRequest support
#include <NewPing.h>         // NewPing version 1.7
#include <avr/wdt.h>         // watchdog


#define MAX_DISTANCE 270 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


const int SONAR_NUM = 3;  
NewPing sonars[SONAR_NUM] = 
{
  NewPing(PB1, PB1, MAX_DISTANCE), // each sensor(trig pin, echo pin, max distance to ping)
  NewPing(PB3, PB3, MAX_DISTANCE),
  NewPing(PB4, PB4, MAX_DISTANCE),
 
};


const int I2CSlaveAddress = 8;      // I2C Address.

int distance[SONAR_NUM];                    // Where the Distance is stored (8 bit unsigned)
int place = 0;
unsigned long start;



void setup()
{
  TinyWireS.begin(I2CSlaveAddress);      // Begin I2C Communication
  TinyWireS.onRequest(transmit);         // When requested, call function transmit()

  wdt_enable(WDTO_500MS);               // Watchdog.  Bite time 500ms
}


void loop()
{
  readDistance();
  wdt_reset();                          // feed the watchdog
}


//-------------------------------------------------------------------

void transmit()
{
  byte hh;
  switch (place) {                    //switch statement like if, tests for each case.
    case 0:
      hh = 255;                       // start byte (255) so data always received in correct order.
      break;
    case 1:
      hh = distance[place - 1];          // Send last recorded distance for current sensor
      break;
    case 2:
      hh = distance[place - 1];        // Send last recorded distance for current sensor
      break;
    case 3:
     hh = distance[place - 1];        // Send last recorded distance for current sensor
      break;
    
  }
  TinyWireS.send(hh);
  place++;
  if (place > SONAR_NUM) place = 0;
}

void readDistance()
{
  
  for(int i = 0; i < SONAR_NUM; i ++)
  {
    distance[i] = sonars[i].ping_cm();
    if(distance[i] > 254 || distance[i] == 0) distance[i] = 254;
    delay(20);
  }
}

