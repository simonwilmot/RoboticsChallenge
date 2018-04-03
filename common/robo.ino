/*

  V 1.0 - 15/03/14  - Backend code for the robotics - same code master - will be overwritten
  V 1.1 - 21/08/14  - Updated to include new challenges
  V 1.2 - 23/03/15  - Cleaned up and simplified
  V 1.3 - 10/05/16  - Updated to fix minor bugs
  
  Robotics Challenge - - all supporting code

  Also has a TestAll function you use to test all components are working

*/

//Look in robo.h for all the #defines

// New ping stuff - wont need library as the CPP is included in sketch
#include <NewPing.h>
#include <Servo.h> // need the standard Arduino servo library

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_PING_RANGE);

// Pan and tilt servo objects
Servo panServo, tiltServo;

// The setup routine runs once when you press reset:
// This must be here to set your pins for the motor and do some initialisation
void setup()
{                
  // initialize the digital pins we will use as an output for the Motors
  pinMode(L1, OUTPUT);     
  pinMode(L2, OUTPUT);     
  pinMode(L3, OUTPUT);     
  pinMode(L4, OUTPUT);
      
  Serial.begin(115200);  // Start the Serial and make sure the debug says 115200 
  Serial.println("Starting Barclays Robot");
  
  tiltCentre();
  pointCentre();
  
  //while(1)  // Use this to repeat forever
  // testAll();

}

int readLineSensor(int pin)
{
  int sensorSignal = 0;
  
  for ( int i=0; i < SAMPLE_SIZE_LINE; i++ )
  {
    sensorSignal += analogRead(pin);// Read value from sensor  
  }
   
  sensorSignal /= SAMPLE_SIZE_LINE;
  
  //Always returns 0 or 1, but whether that means BLACK or WHITE can be changed in robo.h depending on the sensor version.
  if ( sensorSignal < LINE_THRESHOLD )
    return 0;
    
  return 1;  
}


int rightLineSensor()
{
  int val = readLineSensor(RIGHT_LINE);
  Serial.println("Right Line Sensor: " + val);
  return val;
}

int leftLineSensor()
{
  int val= readLineSensor(LEFT_LINE);
  Serial.println("Left Line Sensor: " + val);
  return val;
}

// robMove routine switches the correct inputs to the L298N for the direction selected.
void robMove(int l1, int l2, int r1, int r2)
{
  analogWrite(L1, l1);
  digitalWrite(L2, l2);
  analogWrite(L3, r1);
  digitalWrite(L4, r2);  
}

void reverse(int wait, int vSpeedLeft, int vSpeedRight)
{
  if ( vSpeedLeft > 255 ) 
    vSpeedLeft = 255;

  if ( vSpeedRight > 255 ) 
    vSpeedRight = 255;

  Serial.println("Moving Backwards: Speed Left and Right: " + String(vSpeedLeft) + " " + String(vSpeedRight));
  robMove(255-vSpeedLeft, HIGH, 255-vSpeedRight, HIGH);    // when reversing, the speed needs to be opposite, so subtract from 255
  delay(wait);
  
  //Amended to stop after the wait time
  halt(0);
}

void forward(int wait,int vSpeedLeft,int vSpeedRight)
{
  if ( vSpeedLeft > 255 ) 
    vSpeedLeft = 255;

  if ( vSpeedRight > 255 ) 
    vSpeedRight = 255;

  Serial.println("Moving Forwards: Speed Left and Right: " + String(vSpeedLeft) + " " + String(vSpeedRight));
  robMove(vSpeedLeft, LOW, vSpeedRight, LOW);
  delay(wait);
  
  //Amended to stop after the wait time
  halt(0);
}

void rightSpin(int wait, int vSpeed)
{
  Serial.println("Spinning right");
  robMove(vSpeed, LOW, 255 - vSpeed, HIGH);
  delay(wait);
  
  //Amended to stop after the wait time
  halt(0);
}

void leftSpin(int wait,int vSpeed)
{
  Serial.println("Spinning left");
  robMove(255 - vSpeed, HIGH, vSpeed, LOW);
  delay(wait);
  
  //Amended to stop after the wait time
  halt(0);
}


void halt(int wait)
{
  Serial.println("Stopping");
  robMove(0, LOW, 0, LOW);
  delay(wait);
}


boolean leftObstacleSensor()
{
 
  if ( digitalRead(LEFT_OBSTACLE) == 0 ) // Test left sensor
  {
    Serial.println("Left Obstacle Detected");
    return true;
  }
  
  return false;
}

boolean rightObstacleSensor()
{
 
  if ( digitalRead(RIGHT_OBSTACLE) == 0 ) // Test left sensor
  {
    Serial.println("Right Obstacle Detected");
    return true;
  }
  
  return false;
}


int Ultrasonic()
{
 
  int cm=0;
  unsigned int pingTime=0;
  Serial.print("Sonar Ping: ");  
  
  for ( int i=0; i < SAMPLE_SIZE_ULTRA; i++)
  {
    pingTime = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    delay(SONAR_WAIT);                      // Wait between pings, 20ms should be the shortest delay between pings.
    cm += pingTime / US_ROUNDTRIP_CM;
  }
  
  cm /= SAMPLE_SIZE_ULTRA;
  
  if ( cm == 0 || cm > MAX_PING_RANGE) 
    cm = MAX_PING_RANGE;  // Clear!

  Serial.print(cm);
  Serial.println("cm");
  
  return cm;
}


void pointLeft()
{
  panServo.attach(PAN_PIN); 
  panServo.write(SERVO_LEFT);
  Serial.println("Point Left");
  delay(SERVO_WAIT); // wait for servo to get there
  panServo.detach();
}

void pointRight()
{
  panServo.attach(PAN_PIN); 
  panServo.write(SERVO_RIGHT);
  Serial.println("Point Right");
  delay(SERVO_WAIT); // wait for servo to get there
  panServo.detach();
}

void pointCentre()
{
  panServo.attach(PAN_PIN); 
  panServo.write(SERVO_CENTRE);
  Serial.println("Point Centre");
  delay(SERVO_WAIT); // wait for servo to get there
  panServo.detach();
}

void pointValue(int pos)
{
  panServo.attach(PAN_PIN);
  Serial.print("Point Value: ");
  Serial.println(pos);
  panServo.write(pos);
  delay(SERVO_WAIT); // wait for servo to get there
  panServo.detach();
}


void tiltUp()
{
  tiltServo.attach(TILT_PIN);
  tiltServo.write(SERVO_UP);
  Serial.println("Tilt Up");
  delay(SERVO_WAIT); // wait for servo to get there
  tiltServo.detach();
}

void tiltDown()
{
  tiltServo.attach(TILT_PIN);
  tiltServo.write(SERVO_DOWN);
  Serial.println("Tilt Down");
  delay(SERVO_WAIT); // wait for servo to get there
  tiltServo.detach();
}

void tiltCentre()
{
  tiltServo.attach(TILT_PIN);
  tiltServo.write(SERVO_CENTRE);
  Serial.println("Tilt Centre");
  delay(SERVO_WAIT); // wait for servo to get there
  tiltServo.detach();
}

void tiltValue(int pos)
{
  tiltServo.attach(TILT_PIN);
  Serial.print("Tilt Value: ");
  Serial.println(pos);
  tiltServo.write(pos);
  delay(SERVO_WAIT); // wait for servo to get there
  tiltServo.detach();
}

void testAll()
{
  long startTime;  // Captures startTime in clock time - time is milliseconds between them
  long endTime;
  
  // ROBOTEERS this is the test all function - setup() will execute this once or it needs to be called from loop()
  
  Serial.println("TESTING MOVEMENT SHOULD TAKE ABOUT 10 seconds");
  Serial.println("FULL POWER 255");
  forward(1000,255,255);
  halt(1000);
  
  reverse(1000,255,255);
  halt(1000);
 
  Serial.println("HALF POWER 180");
  forward(1000,180,180);
  halt(1000);
  
  reverse(1000,180,180);
  halt(1000);
  
  
 Serial.println("NOW TESTING PAN AND TILT 5 TIMES");
 Serial.println("TESTING PAN 5 TIMES - PLEASE ENSURE THIS IS A PAN ACTION");
 
  for ( int i=0;i<5;i++)
  {
    pointCentre();
    delay(500);
    pointLeft();
    delay(500);
    pointRight();
    delay(500);
    pointCentre();
    
    delay(1000);
  }
  
 Serial.println("TESTING TILT 5 TIMES - PLEASE ENSURE THIS IS A TILT ACTION");
 
  for ( int i=0;i<5;i++)
  {
    tiltCentre();
    delay(500);
    tiltUp();
    delay(500);
    tiltDown();
    delay(500);
    tiltCentre();
    
    delay(1000);
  }
 
  
  Serial.println("NOW TESTING OBSTACLE SENSORS FOR 30 SECONDS ");
  Serial.println("TEST SENSOR NOW PLEASE - TILT and PAN SENSOR WILL MOVE");

  startTime = millis();
  endTime = millis();
  
  while(endTime-startTime < 30000)
  {
    
    if ( leftObstacleSensor() == true )
    {
       pointLeft();
       tiltUp();
    }
  
    if ( rightObstacleSensor() == true )
    {
       pointRight();
       tiltDown();
    }
    
    endTime = millis();
  }
  
  Serial.println("NOW TESTING ULTRASONIC SENSORS FOR 30 SECONDS ");
  Serial.println("TEST SENSOR BY PLACING YOUR HAND OR OBJECT IN FRONT OF ULTRASONIC ( EYES)");
  Serial.println("IF THE DISTANCE IS LESS THAN 90CM IT SHOULD PRINT");

  startTime = millis();
  endTime = millis();
  
  while(endTime-startTime < 30000)
  {

    int cm =  Ultrasonic();
    
    if ( cm < 90 ) {
      Serial.print("Distance is: ");
      Serial.println(cm);
    }
    
    endTime = millis();
  }
  
    pointCentre();
    tiltCentre();
  
  Serial.println("NOW TESTING LINE FOLLOW SENSORS FOR 30 SECONDS ");
  Serial.println("TEST SENSOR NOW PLEASE USING BLACK or WHITE for EACH SENSOR");

  startTime = millis();
  endTime = millis();
  
  while(endTime-startTime < 30000)
  {
    
    if ( leftLineSensor() == BLACK ) 
      Serial.println("LEFT SENSOR READS BLACK");
   
   
    if ( leftLineSensor() == WHITE )    
     Serial.println("LEFT SENSOR READS WHITE");
    
    if ( rightLineSensor() == BLACK ) 
      Serial.println("RIGHT SENSOR READS BLACK");
   
   
    if ( rightLineSensor() == WHITE )    
     Serial.println("RIGHT SENSOR READS WHITE");
    
    endTime = millis();
  }
   
}




