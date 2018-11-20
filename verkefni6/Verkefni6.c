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


task main()
{
	StartTask(stopButton);
	//StartTask(holdArm);
	//StartTask(stopWhenDark);
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
	SensorValue[rightEncoder] = 0; // Reset the right encoder value so the robot doesn't go too far
	const float rotations = 1.5; // How many rotations for 0.5m
	float direction = 1.0; // Is the robot supposed to drive forward or backwards
	int runNum = 0; // Used to calculate the distance to drive


	float goalDist = (rotations * 2.8 * 360);
	//drive(goalDist, 0.5/*(direction / 2)*/);
	//turn(90, 0.5);
	while (true){
		while(abs(SensorValue[leftEncoder]) <= goalDist || abs(SensorValue[rightEncoder]) < goalDist){
			followLine();
		}
		turn(20, 0.7);
		//StartTask(followLine);
		goalDist = (rotations * 0.5 * 360);
		while(abs(SensorValue[leftEncoder]) <= goalDist || abs(SensorValue[rightEncoder]) < goalDist){
			followLine();
		}
		turn(150, 0.7);
		while(abs(SensorValue[leftEncoder]) <= goalDist || abs(SensorValue[rightEncoder]) < goalDist){
			followLine();
		}
		goalDist = (rotations * 2.2 * 360);
		turn(20, -0.7);
		while(abs(SensorValue[leftEncoder]) <= goalDist || abs(SensorValue[rightEncoder]) < goalDist){
			followLine();
		}
		/*
		writeDebugStreamLine("Left: %d", SensorValue[lineLeft]);
		writeDebugStreamLine("Mid: %d", SensorValue[lineMid]);
		writeDebugStreamLine("Right: %d", SensorValue[lineRight]);
		*/
		StopAllTasks();
	}
}
