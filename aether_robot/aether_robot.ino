/**
aether_robot.ino
Arduino robot vehicle firmware
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2iQXvlL
*/

#include <Wire.h>
#include <avr/wdt.h> // watchdog
#include "robot.h"

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



