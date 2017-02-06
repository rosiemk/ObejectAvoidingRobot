/**
software_serial.cpp
Send bearing and distance information via Serial communication to NodeMCU.
*/

#include "software_serial.h"

//namespace::class::constructor
Aether::Software_Serial::Software_Serial(int RX, int TX)
//initialiser list and variables, comma separated
: receivePin(RX), transmitPin(TX), mySerial(receivePin, transmitPin)

    {
     mySerial.begin(9600);
     pinMode(receivePin, INPUT);
     pinMode(transmitPin, OUTPUT);
    }

// ----------Public methods--------------------
void Aether::Software_Serial::sendData(String data)
{
  mySerial.println(data);
}

