/* Object avoiding robot with 3 ultrasonic sensors connected via I2C bus and ATtiny85. 
 *  This is the master sketch. 
 *  Slave programme for ATtiny85 is: newslave_3sensors_attiny85_21dec.ino
*/

#include <NewPing.h>
#include <Wire.h>
#include <avr/wdt.h> //watchdog

//I2C 
const int I2CAddress = 8;

#define LEFT 0
#define MIDDLE 1
#define RIGHT 2

int place; //current sensor
byte distance[3]; //distance array of 3 values
int dist_min;
int dir_min; //direction set by dist_min

//Motor 1 (right)
#define E1 5  // Enable PWM
#define F1 9  // Control 1
#define B1 8  // Control 2

//Motor 2 (left)
#define E2 11  // Enable PWM
#define F2 12  // Control 1
#define B2 13  // Control 2

// Distance measurements
const int dangerThresh = 15; //threshold for obstacles (cm)
const int mapThresh = 30; //threshold for mapping objects, below this number (cm).  Is this value useful or can I just use the other two?
const int randomThresh = 40; //threshold for initating random route planning (cm)

int pwmSpeed = 0;
int maxSpeed = 100; // max motor speed

// Accelleration/deceleration
const long accel_int = 8; //time (ms) for acceleration loop.  Lower number = faster acceleration
const long decel_int = 8; //time(ms) for deceleration loop. Low number = faster decceleration
unsigned long prevAccTime = 0; // previous time during acceleration to measure interval

// turnRight/Left
int turnSpeed = 0;
bool hasTurned = false;

const long turn_int = 500; //time(ms) for turn.
unsigned long prevTime = 0; // make prev time for turn right/left and stand?

//Stand
const long stand_int = 500; //time(ms) for stand. 
bool standing = false;

unsigned long currentMillis = 0; // store current time

//int leftDistance, rightDistance; //distances on either side

void setup() {
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
    pinMode(F1, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(F2, OUTPUT);
    pinMode(B2, OUTPUT);

    Wire.begin();
    Serial.begin(115200);

//   wdt_disable();
}

void loop() {
  stand(500);

/*wdt_enable(WDTO_1S); //watchdog.  Bite time 500ms.

readDistance();
 
 if(dist_min > randomThresh){
  forwards();
  }
  else if(dist_min > mapThresh && dist_min <= randomThresh){
    backwards();
  }
  else{
    turnRight();
    Serial.println("r");
    if (dist_min > dangerThresh && dist_min <= mapThresh){
      turnLeft();
      }
      else{
        backwards();
        }
      }
    
 


  

 /* readDistance();

        if(dist_min > dangerThresh){
          forwards();
          //lots of room, move forwards
          }
        else if(dist_min <=randomThresh && dist_min > dangerThresh){ // if path is blocked
          stand();
          
          if(dir_min == LEFT || dir_min == MIDDLE){
            turnRight();
            }
          else{ // dir_min == RIGHT
            turnLeft();
            }
          }
         else{ // if dist_min <=dangerThresh
            stand();
            backwards();
          }
*/
          
           
            
          /*pseudo: if(distance_min == LEFT){
                      turnright();
                      Serial.println("turning right");
                       }
                       else if(distance_min == RIGHT){
                       turnleft(); how much?
                       Serial.println("turning left");
                       else{
                       backwards(); for how long?
                       Serial.println("reverse");
                       }
                       }
          
          
        }
      
      Serial.println();         
*/



     

//wdt_reset();

}

//-------------------------------------------------------------

void readDistance(){
  //Serial.print("L");
  while(readTiny(I2CAddress)<255) {
    Serial.print("WT"); //waiting for first byte
    }
  for (place = 0; place < 3; place++){
    distance[place] = readTiny(I2CAddress);
    }

/*for (int i = 0; i < 3; i++) {
      Serial.print(distance[i]);
      Serial.print(" ");
      }
      Serial.println();
      delay(10);
*/

  if (distance[LEFT] < distance[MIDDLE] && distance[LEFT] < distance[RIGHT]){
    dist_min = distance[LEFT];
    dir_min = LEFT;
   // Serial.print("LEFT");
    }
  else {
    if(distance[MIDDLE] < distance[RIGHT]){
      dist_min = distance[MIDDLE];
      dir_min = MIDDLE;
    //  Serial.print("MIDDLE");
      }
     else{
      dist_min = distance[RIGHT];
      dir_min = RIGHT;
    //  Serial.print("RIGHT");
      }
    }
//    if (distance[MIDDLE] >50){
//      dist_min = distance[MIDDLE];
//      dir_min = "MIDDLE";
//      Serial.println("MIDDLE");
//      }

//Serial.println(dist_min);


delay(10);

} 

// ** BYTE ** -----------------------------------------------------------
byte readTiny(int address) 
{
  byte hh ;
  long entry = millis();
  Wire.requestFrom(address, 1);                  // The TinyWire library only allows for one byte to be requested at a time
  while (Wire.available() == 0 && (millis() - entry) < 100)  Serial.print("W");
  if  (millis() - entry < 100) hh = Wire.read();
  return hh;
}

// ** DIRECTIONS ** -----------------------------------------------------------

void forwards() {
    analogWrite(E1, 150);            
    analogWrite(E2, 150);
    
    digitalWrite(F1, HIGH); // set direction
    digitalWrite(B1, LOW);
    digitalWrite(F2, HIGH);
    digitalWrite(B2, LOW);

   //**acceleration**
   
/*   currentMillis = millis();
   if(currentMillis - AccTime >= accel_int){
    prevAccTime = currentMillis;
    if(pwmSpeed < maxSpeed){
      pwmSpeed +=5; // increase for faster acceleration
      }
     
      analogWrite(E1, pwmSpeed);            
      analogWrite(E2, pwmSpeed);

    }
    else if(pwmSpeed == maxSpeed){
      analogWrite(E1, pwmSpeed);            
      analogWrite(E2, pwmSpeed);
      }
 */
  }

void backwards()
{
  // accelleration? 
  analogWrite(E1, 150); // 0 to 255
  analogWrite(E2, 150);
  

  digitalWrite(F1, LOW);
  digitalWrite(B1, HIGH);
  digitalWrite(F2, LOW);
  digitalWrite(B2, HIGH);
  }
    
void turnRight() {
  hasTurned = false;
  

  digitalWrite(F1, LOW);
  digitalWrite(B1, HIGH);
  digitalWrite(F2, HIGH);
  digitalWrite(B2, LOW);

  currentMillis = millis();

  if(currentMillis - prevTime > turn_int && hasTurned == false)
  {
    prevTime = currentMillis;

    if(turnSpeed == 0){
      turnSpeed = 150;
    }
    else{
      turnSpeed = 0;
      hasTurned = true;
      }
      analogWrite(E1, turnSpeed);
      analogWrite(E2, turnSpeed);
      Serial.println(turnSpeed);
    }
    
    if(turnSpeed == 0 && hasTurned == true) {
      Serial.println("done");
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW); 
      }
}
  

void turnLeft()
{ 
  hasTurned = false;
  
  digitalWrite(F1, HIGH);
  digitalWrite(B1, LOW);
  digitalWrite(F2, LOW);
  digitalWrite(B2, HIGH);
  
  currentMillis = millis();
  
  if (currentMillis - prevTime > turn_int && hasTurned == false){ //add time since last turn variable?
    prevTime = currentMillis; // event listener, record time

      if(turnSpeed == 0){
        turnSpeed = 150;
      } 
       else{
          turnSpeed = 0;
          hasTurned = true;
       }
        analogWrite(E1, turnSpeed);
        analogWrite(E2, turnSpeed);   
      }  
        if (turnSpeed == 0 && hasTurned == true){
        Serial.println("done");
        digitalWrite(E1, LOW);
        digitalWrite(E2, LOW); 
        }  
}

void stand(int stand_int) // arg is stand time
{
 currentMillis = millis(); //start timer

 if(currentMillis - prevTime > stand_int) {
  prevTime = currentMillis;
  
  if(standing == false){
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  standing = true;
  } 
  else{
    standing = false;
  }
  
  Serial.println(standing);
 }
 
}




//**decceleration** from forwards motion
/*  digitalWrite(F1, HIGH);
    digitalWrite(B1, LOW);
    digitalWrite(F2, HIGH);
    digitalWrite(B2, LOW);

 
  currentMillis = millis();
  if(currentMillis-prevAccTime >= decel_int){
    prevAccTime = currentMillis;
    if(pwmSpeed > 8){ // * pwmSpeed values must match
      pwmSpeed-=8; // (*) as above
      analogWrite(E1, pwmSpeed);
      analogWrite(E2, pwmSpeed);
      
//      Serial.print("-"); 
//      Serial.println(pwmSpeed);
      }
     else if(pwmSpeed <= 8){ // (*) as above 
      pwmSpeed == 0;
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);
      }
    }
 */



// NOTES  -----------------------------------------------------------

//direction library?

//make function for reverse-right and reverse-left - turning slowly to remeasure



// 1.  Danger routine using dangerThresh var < 10cm
      // find out where objet is, get to tracking distance from object.
      // send object data to virtual world.

// 2. Mapping distance routinge using trackingThresh var <30cm
      // tracking obstacle for xseconds or random time before going before initating random route planning.
      // send object data to virtual world

// 3. Random route planning routine using randomThresh var <50cm
      // every x number of seconds turn by random amount.




//compare distance function? linking to route plotting.?

