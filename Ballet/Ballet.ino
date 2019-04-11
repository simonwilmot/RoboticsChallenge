#include "robo.h"
// A simple sketch for doing a ballet

void loop()
{
	// Basic code for the ballet

	forward(1000, 255, 255);
	halt(500);

	reverse(1000, 255, 255);
	halt(500);

	leftSpin(2000, 255);
	halt(500);

	rightSpin(2000, 255);
	halt(500);

	forward(1000, 255, 255);
	halt(500);

	leftSpin(800, 255);
	halt(500);

	forward(500,255, 255);
	halt(500);

	reverse(1000, 255, 255);
	halt(500);

	// SHOOGLE!!!

	rightSpin(800, 255);
	halt(500);
	shoogle();

	rightSpin(800, 255);
	halt(500);
	shoogle();

	leftSpin(500, 255);
	halt(500);
	shoogle();

	leftSpin(500, 255);
	halt(500);
	shoogle();

	leftSpin(3000, 255);
	halt(500);

	return;
}

void shoogle()
{
	int i=0;

	i = 5;
	while (i>0)
	{
		forward(100, 255, 255);
		halt(200);

		reverse(100, 255, 255);
		halt(200);

		i--;
	}
}
