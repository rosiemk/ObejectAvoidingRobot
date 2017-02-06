/*
*   software_serial.h
*   Send bearing and distance information via Serial communication to NodeMCU.
*/
#pragma once
#include <SoftwareSerial.h>
#include <Arduino.h>

namespace Aether
{
  class Software_Serial
  {
    private:
    int receivePin;
    int transmitPin;

    //any private methods

    public:
    //public variables
    //public methods
    void sendData(String data);
    SoftwareSerial mySerial;
    Software_Serial(int RX, int TX); // constructor
    
  };
};

