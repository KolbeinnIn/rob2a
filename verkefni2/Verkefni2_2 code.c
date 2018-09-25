#pragma config(Motor,  port4, leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorNormal, openLoop)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)

#include "../GlobalFunctions/Functions.c"

const float rotations = 1.5;
float direction = 1.0;
int runNum = 0;

void driveSuicide(int *i)
{
	SensorValue[leftEncoder] = 0;
	writeDebugStreamLine("%d", direction);

	if(*i % 2 == 0)
		runNum++;

	float goalDist = (rotations * runNum * 360);
	writeDebugStreamLine("%f Goal", goalDist);

	while(abs(SensorValue[leftEncoder]) < goalDist)
	{
		drive(direction / 2);
		//writeDebugStreamLine("Takki: %d", SensorValue[touchSensor]);
		//writeDebugStreamLine("%d Sensor", SensorValue[leftEncoder]);
	}

	drive(0);

	writeDebugStreamLine("Left encoder value: %d", SensorValue[leftEncoder]);

	direction *= -1;
}

task main()
{
	StartTask(stopButton);
	//writeDebugStreamLine("Takki: %d", SensorValue[touchSensor]);

	for (int i = 0; i < 10; i++)
	{
		driveSuicide(&i);
	}

	StopAllTasks();
}
