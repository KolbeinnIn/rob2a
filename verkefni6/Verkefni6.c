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

void followDrive(int deg, float speed, float dist, int){
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
	SensorValue[rightEncoder] = 0;
	while((abs(SensorValue[rightEncoder]) + abs(SensorValue[leftEncoder])) / 2 < dist){
			followLine();
	}
	while (true){
		if (SensorValue[sonarSensor] <= 12){
			motor[leftMotor] = -40;
			motor[rightMotor] = -40;
		}
		else if (SensorValue[sonarSensor] > 16){
			motor[leftMotor] = 40;
			motor[rightMotor] = 40;
		}
		else
			break;
	}
	turn(deg,speed);
}
float goalDist = 0;
const float rotations = 1.5; // How many rotations for 0.5m
const int sMainLine = 12;
task main()
{
	StartTask(stopButton);
	//StartTask(holdArm);
	//StartTask(stopWhenDark);
	while (true){
		writeDebugStreamLine("%d", SensorValue(sonarSensor));
		/*
		goalDist = (rotations * 2.8 * 360);
		followDrive(90,0.7,goalDist); //drive 2m, turn 90 degrees right

		goalDist = (rotations * 0.4 * 360);
		followDrive(180,0.7,goalDist); //drive 0.5m, turn 180 degrees right
		followDrive(90,-0.7,goalDist); //drive 0.5m, turn 90 degrees left

		goalDist = (rotations * 2 * 360);
		followDrive(90,0.7,goalDist);

		/*
		writeDebugStreamLine("Left: %d", SensorValue[lineLeft]);
		writeDebugStreamLine("Mid: %d", SensorValue[lineMid]);
		writeDebugStreamLine("Right: %d", SensorValue[lineRight]);
		*/
		//StopAllTasks();
	}
}
