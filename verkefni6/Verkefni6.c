#pragma config(Motor,  port4, leftMotor,    tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorVex269, openLoop)
#pragma config(Motor,  port5, armMotor,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port3, clawMotor,    tmotorVex269, openLoop, reversed)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)
#pragma config(Sensor, in1, potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1, sonarSensor,  sensorSONAR_cm)
#pragma config(Sensor, in2, lightSensor,  sensorReflection)
#pragma config(Sensor, in3, lineLeft,   sensorLineFollower)
#pragma config(Sensor, in4, lineMid,  sensorLineFollower)
#pragma config(Sensor, in5, lineRight,    sensorLineFollower)

#include "../GlobalFunctions/Functions.c"

const float rotations = 1.5; // How many rotations for 0.5m
const int revolutions = 360;
float goalDist = 0;
float distances[] = {2,  0.3, 0.25, 1.5, -1, 1,  0.5, 0.5, 1,  -1, 0.5, 0.5, 0.5, 0.5, -1}; /* -1 is a box drop */
int sonarValues[] = {15, 33,  76,   66,  -1, 62, 33,  76,  66, -1, 111, 38,  76,  66,  -1}; /* -1 is a box drop */
int turnDir[] =     {1,  1,   -1,   1,   0,  -1, 1,   1,   1,  0,  1,   1,   -1,  1,   0}; /* 0 is box drop */
bool pickup[] =     {0,  1,   0,    0,   0,  0,  1,   0,   0,  0,  0,   1,   0,   0,   0};

void followDrive(float mSpeed, float dist, int sonarDist){
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
	SensorValue[rightEncoder] = 0;

	sonarDist += 5;
	dist *= 2;

	while(abs(SensorValue[rightEncoder]) < dist){
			if (dist == 0){
				break;
			}
			followLine();
	}

	motor[leftMotor] = 0;
	motor[rightMotor] = 0;

	wait1Msec(500);

	while (true){
		if (SensorValue[sonarSensor] <= sonarDist - 2){
			motor[leftMotor] = -40;
			motor[rightMotor] = -40;
		}
		else if (SensorValue[sonarSensor] >= sonarDist + 2){
			motor[leftMotor] = 40;
			motor[rightMotor] = 40;
		}
		else
			break;
	}

	motor[leftMotor] = 0;
	motor[rightMotor] = 0;

	wait1Msec(500);
	//writeDebugStreamLine("before turn");
	turn(10, mSpeed);

	do {
		turn(5, mSpeed);
	} while(!findLine());
}

int len = sizeof(distances) / sizeof(distances[0];
int light = SensorValue(lightSensor);
task taskMain()
{
	while (true){
		for (int i = 4; i < sizeof(distances) / sizeof(distances[0]); i++)
		{
			if (distances[i] == -1) // Drop the glass in the box
			{
				while(findLine())
				{
					if(!findLine())
						break;

					followLine(-10);
				}

				motor[leftMotor] = 0;
				motor[rightMotor] = 0;

				motor[clawMotor] = 20;
				wait1Msec(200);
				motor[clawMotor] = 0;
			}
			else
			{
				goalDist = (rotations * distances[i] * revolutions);
				followDrive(0.7 * turnDir[i], goalDist, sonarValues[i]);
				wait1Msec(500); // Give the robot time to think
			}
		}
		StopAllTasks();
	}
}

task main()
{
	StartTask(stopButton);
	StartTask(stopWhenDark);
	while (true){}
}
