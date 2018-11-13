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
#pragma config(Sensor, in3, lineRight,   sensorLineFollower)
#pragma config(Sensor, in4, lineMid,  sensorLineFollower)
#pragma config(Sensor, in5, lineLeft,    sensorLineFollower)

#include "../GlobalFunctions/Functions.c"
const int speed = 45;

task main()
{
	StartTask(stopButton);
	//StartTask(holdArm);
	//StartTask(stopWhenDark);
	int thresholdL = 1651;
	int thresholdM = 1720;
	int thresholdR = 1852;
	int threshold = 1700;
	while (true){
		/*
		writeDebugStreamLine("Left: %d", SensorValue[lineLeft]);
		writeDebugStreamLine("Mid: %d", SensorValue[lineMid]);
		writeDebugStreamLine("Right: %d", SensorValue[lineRight]);
		*/
		if(SensorValue(lineRight) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = -speed;
      motor[rightMotor] = speed;
    }
    // CENTER sensor sees dark:
    if(SensorValue(lineMid) > threshold)
    {
      // go straight
      motor[leftMotor]  = speed;
      motor[rightMotor] = speed;
    }
    // LEFT sensor sees dark:
    if(SensorValue(lineLeft) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = speed;
      motor[rightMotor] = -speed;
    }
    /*else{
    	motor[leftMotor]  = -50;
      motor[rightMotor] = -50;
    }*/
	}

	StopAllTasks();
}
