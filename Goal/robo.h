//A set of defines which can be tweaked to reconfigure or tune the robot

//Define which Arduino pin is connected to what
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define LEFT_LINE A4 //Left line follow sensor
#define RIGHT_LINE A5 //Right line follow sensor

#define LEFT_OBSTACLE 3 //Left obstacle sensor
#define RIGHT_OBSTACLE 2 //Right obstacle sensor

#define PAN_PIN 11 //Pan
#define TILT_PIN 10 //Tilt

#define L1 6 //Motor L1
#define L2 12 //Motor L2
#define L3 5 //Motor L3
#define L4 8 //Motor L4

// If the line follower code needs reversing then set this (new sensors are reversed!)
#define REVERSE_LF true
#ifdef REVERSE_LF
  #define BLACK 1
  #define WHITE 0
#else
  #define BLACK 0
  #define WHITE 1
#endif

//Define the extremities for the servos
#define SERVO_CENTRE 90
#define SERVO_LEFT 135
#define SERVO_RIGHT 45
#define SERVO_UP 45
#define SERVO_DOWN 135

//Define the maximum range for a sonar ping
#define MAX_PING_RANGE 1000

//Define how many times to check the sensors for an average reading (Line follower and Ultrasonic)
#define SAMPLE_SIZE_ULTRA 5
#define SAMPLE_SIZE_LINE 1

//Define how long to wait for a servo to move position
#define SERVO_WAIT 200

//Define how long to wait between ultrasonic samples
#define SONAR_WAIT 30

//Define what value threshold to use for the line followers between BLACK or WHITE
#define LINE_THRESHOLD 500

