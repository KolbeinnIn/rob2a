#pragma config(Motor, port6, rightMotor, tmotorNormal, openLoop)
#pragma config(Motor, port4, leftMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor, port5, armMotor, tmotorNormal, openLoop, reversed)

#include "../GlobalFunctions/Functions.h"

static int timePer50 = 965; // The time it takes (in ms) to go about 50cm

void driveSuicide(int *i){
	if (*i == 4){
		motor[armMotor] =	25;
	}

	drive(0.5);
	wait1Msec(100);
	drive(1);

	writeDebugStreamLine("%d", *i);
	writeDebugStreamLine("%d", timePer50 * (*i+1) - 100);

	wait1Msec(timePer50 * (*i + 1));

	drive(0);
	if (*i == 4){
		motor[armMotor] = 0;
	}
	wait1Msec(300);
	drive(-0.5);
	wait1Msec(100);
	drive(-1);

	wait1Msec(timePer50 * (*i + 1) - 100);
	drive(0);

	wait1Msec(200);
}

task main()
{
	//motor[armMotor] = 10;

	for (int i = 0; i < 5; i++)
	{
		driveSuicide(&i);
	}
}
