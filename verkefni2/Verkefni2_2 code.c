#pragma config(Motor,  port4, leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorNormal, openLoop)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)

#include "../GlobalFunctions/Functions.c"

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Verkefni 2.2 -                                           *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program makes the robot drive a suicide, first 0.5m, then 1m, 1.5m and so on based on the    *|
|*  encoder.                                                                                          *|
|*                                        ROBOT CONFIGURATION                                         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 6        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 4        leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital Port 5      leftEncoder         VEX 2-wire module     Left side encoder                 *|
|*    Digital Port 3      rightEncoder        VEX 2-wire module     Right side encoder                *|
|*    Digital Port 12     touchSensor         VEX 2-wire module     Fron button                       *|
\*----------------------------------------------------------------------------------------------------*/

const float rotations = 1.5; // How many rotations for 0.5m
float direction = 1.0; // Is the robot supposed to drive forward or backwards
int runNum = 0; // Used to calculate the distance to drive

void driveSuicide(int *i)
{
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
	writeDebugStreamLine("%d", direction);

	if(*i % 2 == 0) runNum++;

	float goalDist = (rotations * runNum * 360);
	writeDebugStreamLine("%f Goal", goalDist);

	while(abs(SensorValue[leftEncoder]) < goalDist || abs(SensorValue[rightEncoder]) < goalDist)
		drive(direction / 2); // Drive at half speed

	drive(0);

	writeDebugStreamLine("Left encoder value: %d", SensorValue[leftEncoder]);

	direction *= -1; // Swap the direction
}

task main()
{
	StartTask(stopButton);

	// Run 10 times
	for (int i = 0; i < 10; i++)
		driveSuicide(&i);

	StopAllTasks();
}
