#pragma config(Motor, port6, rightMotor, tmotorNormal, openLoop)
#pragma config(Motor, port4, leftMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor, port5, armMotor, tmotorNormal, openLoop, reversed)

#include "../GlobalFunctions/Functions.h"

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Verkefni 2.1 -                                           *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program makes the robot drive a suicide, first 0.5m, then 1m, 1.5m and so on                 *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 6        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 4        leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Motor Port 5        armMotor            VEX 3-wire module     Arm lifting motor                 *|
\*----------------------------------------------------------------------------------------------------*/

static int timePer50 = 965; // The time it takes (in ms) to go about 50cm

void driveSuicide(int *i){
	if (*i == 4) motor[armMotor] =	25; // Raise the arm on the last run to avoid the wall

	drive(0.5);
	wait1Msec(100); // Accelerate slower

	drive(1);

	/*********/
	/* DEBUG */
	/*********/
	writeDebugStreamLine("%d", *i);
	writeDebugStreamLine("%d", timePer50 * (*i+1) - 100);

	wait1Msec(timePer50 * (*i + 1)); // Waits for the time it takes to drive around 50cm * the run + 1

	if (*i == 4) motor[armMotor] = 0;

	drive(0);
	wait1Msec(300); // Waits between runs to avoid tipping over

	drive(-0.5);
	wait1Msec(100);

	drive(-1);
	wait1Msec(timePer50 * (*i + 1) - 100);

	drive(0);
	wait1Msec(300); // Waits between runs to avoid tipping over
}

task main()
{
	// Runs 5 times
	for (int i = 0; i < 5; i++)
	{
		driveSuicide(&i);
	}
}
