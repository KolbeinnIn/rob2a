#pragma config(Motor,  port4, leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorNormal, openLoop)
#pragma config(Motor,  port5, armMotor,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3, clawMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)
#pragma config(Sensor, in1, potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1, sonarSensor,  sensorSONAR_cm)
#pragma config(Sensor, in2, lightSensor,  sensorReflection)

void drive(float dist, float mul);
task verk4();
#include "../GlobalFunctions/Functions.c"


task main()
{
	StartTask(stopButton);
	StartTask(holdArm);
	StartTask(stopWhenDark);
	while (running){}
	StopAllTasks();
}

task verk4(){
	while(true)
	{
		while(SensorValue(sonarSensor) > 40)
		{
			drive(-1,1);
		}
		turn(60);
	}
}
