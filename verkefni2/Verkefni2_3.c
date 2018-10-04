#pragma config(Motor,  port4, leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorNormal, openLoop)
#pragma config(Motor,  port5, armMotor, tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)
#pragma config(Sensor, in1, potentiometer, sensorPotentiometer)

#include "../GlobalFunctions/Functions.c"

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Verkefni 2.3 -                                           *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program makes the robot drive 0.5m, turn left 90°, drive 0.5m, turn right 90°, drive 0.5m    *|
|*  turn 90°, drive 0.5m.                                                                             *|
|*                                        ROBOT CONFIGURATION                                         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 6        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 4        leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital Port 5      leftEncoder         VEX 2-wire module     Left side encoder                 *|
|*    Digital Port 7      rightEncoder        VEX 2-wire module     Right side encoder                *|
|*    Digital Port 12     touchSensor         VEX 2-wire module     Front button                      *|
|*    Analog Port 1       potentiometer       VEX 2-wire module     Potentiometer                     *|
\*----------------------------------------------------------------------------------------------------*/

const float rotations = 1.3; // How many rotations for 0.5m
const float goalDist = rotations * 360; // 0.5m
float direction = -0.5; // Is the robot supposed to drive forward or backwards

void driveMaze(int *i)
{
	if (*i > 0) // Swap to right turns after the first turn
		direction = 0.5;

	drive(goalDist, 0.5);
	wait1Msec(500);

	if (*i < 3) // Do not turn after the last drive
		turn(90, direction);

	//writeDebugStreamLine("Left encoder value: %d", SensorValue[leftEncoder]);
}

task main()
{
	StartTask(stopButton);
	StartTask(holdArm);

	for (int i = 0; i < 4; i++)
		driveMaze(&i);

	StopAllTasks();
}
