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
const int speed = 60;

task main()
{
	StartTask(stopButton);
	//StartTask(holdArm);
	//StartTask(stopWhenDark);
	int thresholdR = 2487;
	int thresholdM = 2275;
	int thresholdL = 2360;
	//int threshold = 2374;
	while (true){
		/*
		writeDebugStreamLine("Left: %d", SensorValue[lineLeft]);
		writeDebugStreamLine("Mid: %d", SensorValue[lineMid]);
		writeDebugStreamLine("Right: %d", SensorValue[lineRight]);
		*/
		if(SensorValue(lineRight) > thresholdR)
    {
      // counter-steer right:
      motor[leftMotor]  = speed;
      motor[rightMotor] = -speed;
    }
    // CENTER sensor sees dark:
    if(SensorValue(lineMid) > thresholdM)
    {
      // go straight
      motor[leftMotor]  = 60;
      motor[rightMotor] = 60;
    }
    // LEFT sensor sees dark:
    if(SensorValue(lineLeft) > thresholdL)
    {
      // counter-steer left:
      motor[leftMotor]  = -speed;
      motor[rightMotor] = speed;
    }
	}
	StopAllTasks();
}
