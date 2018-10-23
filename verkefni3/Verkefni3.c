#pragma config(Motor,  port4, leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorNormal, openLoop)
#pragma config(Motor,  port5, armMotor, tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)
#pragma config(Sensor, in1, potentiometer, sensorPotentiometer)

#include "../GlobalFunctions/Functions.c"
//ATH!! connection virkadi aldrei thannig thessi kodi gaeti eda gaeti ekki virkad.
task main()
{
	StartTask(stopButton);
	StartTask(holdArm);
	while(1 == 1)
  {
    //Right side of the robot is controlled by the right joystick, Y-axis
    motor[rightMotor] = vexRT[Ch2];
    //Left side of the robot is controlled by the left joystick, Y-axis
    motor[leftMotor] = vexRT[Ch3];
  }
	StopAllTasks();
}
