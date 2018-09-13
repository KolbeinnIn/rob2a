#pragma config(Motor,  port4,           leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           rightMotor,     tmotorNormal, openLoop)
#pragma config(Sensor, dgtl5,  leftEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,         sensorQuadEncoder)

//const circumference = 10; //centimeters
int distance = 0;
int power = 127;


void driveForward(int distance){
	motor[leftMotor] = power;
	motor[rightMotor] = power;
	wait1Msec(1000);
	writeDebugStreamLine("%d",SensorValue[leftEncoder]);
}

task main()
{
	driveForward(distance);

}
