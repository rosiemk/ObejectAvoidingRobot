/*  This is a simple example that turns an LED on or off when it receives 
 *  a "pulse" message. A pulse is essentially an empty message; all that 
 *  matters is that we received a message to "do something". The sender
 *  could have been a button, as an example.
 */

#include <aether-client.h>
#include <SoftwareSerial.h>

void recvWithStartEndMarkers();

int tPin = D5;
int rPin = D6;

SoftwareSerial mySerial(rPin, tPin); // RX, TX nodemcu 

/* Start the aether client */
AetherClient ae;

  /* Software serial stuff */
  const byte numChars = 32;
  char receivedChars[numChars];
  boolean newData = false;

void setup() 
{
  /* You must either begin serial (any baud rate), or set 
   *  log verbosity to LOG_NONE
   */
  Serial.begin(115200);
  mySerial.begin(9600);

  /* software serial pins */
  pinMode(rPin,INPUT);
  pinMode(tPin, OUTPUT);



  /* There are three levels:
   *  LOG_NONE (no output, do not need to called Serial.begin())
   *  LOG_STANDARD (set by default, some logging)
   *  LOG_VERBOSE (maximum logging)
   */
  ae.setLogVerbosity(LOG_VERBOSE);
  //ae.setCustomUrl("192.168.2.100");
  //ae.setCustomPort(3000);

  /* Stores whether we are connected to an access point yet */
  bool connection = false;

  /* while we are not connected to an access point */
  while(!connection)
  {
    /* Try connecting. You must provide the name of the 
     *  wireless network, and its password. You may
     *  provide an optional paramter specifying how 
     *  many milliseconds to wait before aborting the
     *  connecting attempt (defualt is 30000 milliseconds)
     */
    connection = ae.connectToAP("VM647500-2G", "kmyhvyay");
    //connection = ae.connectToAP("DMC_COLLAB", "elephant");
    // connection = ae.connectToAP("SSID", "PASSWORD", 20000);
  }

  /* Connect to the Aether server. You must provide a 
   *  name for the device, a mode, and a data type.
   *  Possible modes are:
   *  MODE_RECEIVE, MODE_SEND
   *  Possible data types are:
   *  DATA_PULSE,
   *  DATA_BOOL,
   *  DATA_NUMBER,
   *  DATA_STRING
   */
  ae.connectToServer("Robot", MODE_SEND, DATA_STRING);
  /* If you have set the device to receive data, you MUST
   *  provide a function to be called upon receipt of a 
   *  message. This MUST return void, and take a single argument
   *  consistent with the data type. The argumnet may be:
   *  void - for pulse
   *  bool - for boolean
   *  float - for number
   *  const char* - for string
   */
}

void loop() 
{
  recvWithStartEndMarkers();

  
  delay(1000);
  /* You need to call loop within the loop */
  ae.loop();
}

void recvWithStartEndMarkers() 
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (mySerial.available() > 0 && newData == false) 
    {
        rc = mySerial.read();

        if (recvInProgress == true) 
        {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) 
                {
                    ndx = numChars - 1;
                }
            }
            else 
            {
                receivedChars[ndx] = '\0'; // terminate the string
                Serial.println(receivedChars);
                ae.sendData(receivedChars);
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) 
        {
            recvInProgress = true;
        }
    }

    newData = false;
}
