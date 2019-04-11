#include "robo.h"
//This is the Goal sketch.  You need to complete this to score a goal from each of the start positions.
//Use the ultrasonic sensor to work out where the ball is and how far away, then shoot!

void loop()
{
  int leftDistance=0;
  int midDistance=0;
  int rightDistance=0;

  tiltCentre();

  pointLeft();
  leftDistance = Ultrasonic();

  if ( leftDistance <= midDistance && leftDistance <= rightDistance )
  {
    //Shoot!

  }

  halt(1000);

  //Celebrate the goal!
  stupidCelebration();

  //Have a rest
  halt(5000);

}

//Demonstrate using functions
void stupidCelebration()
{
  jiggleBot(3);
  wiggleBot(4);
  noddingBot(5);
}

//Demonstrate for iteration
void jiggleBot (int repeats)
{
  for (int i=0; i<repeats; i++)
  {
    forward(200, 255, 255);
    reverse(200, 255, 255);
  }
}

//Demonstrate while iteration
void wiggleBot (int repeats)
{
  int i = 0;

  while (i < repeats)
  {
    leftSpin(200, 255);
    rightSpin(400, 255);
    leftSpin(200,255);

    i++;
  }
}

//Demonstrate recursion
int noddingBot (int repeats)
{
  tiltUp();
  tiltDown();
  tiltCentre();

  if (repeats < 1)
  {
    return 0;
  }

  return noddingBot(repeats - 1);
}
