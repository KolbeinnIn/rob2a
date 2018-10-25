#pragma config(Motor,  port4, leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorNormal, openLoop)
#pragma config(Motor,  port5, armMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3, clawMotor, tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)
#pragma config(Sensor, in1, potentiometer, sensorPotentiometer)

#include "../GlobalFunctions/Functions.c"

const int deadzone = 20;

task main()
{
	StartTask(stopButton);
	StartTask(holdArm);
	//StartTask(stopArmControl);

	while(1 == 1)
	{
		int potent = SensorValue[potentiometer];

		if(vexRT[Btn8D] == 1)
			writeDebugStreamLine("Potentiometer: %d", potent);

		int tmpLeftStickX = vexRT[Ch4];
		int tmpLeftStickY = vexRT[Ch3];
		int tmpRightStickY = vexRT[Ch2];

		if((tmpLeftStickY < -deadzone || tmpLeftStickY > deadzone) || (tmpLeftStickX < -deadzone || tmpLeftStickX > deadzone))
		{
			motor[rightMotor] = vexRT[Ch3] - vexRT[Ch4];
	    motor[leftMotor] = vexRT[Ch3] + vexRT[Ch4];
    }
    else
    {
    	motor[leftMotor] = 0;
    	motor[rightMotor] = 0;
		}
		if (tmpRightStickY < -deadzone || tmpRightStickY > deadzone)
		{
    	motor[armMotor] = vexRT[Ch2];
		}
		else
		{
			motor[armMotor] = 0;
		}

    if(vexRT[Btn6U])
    	motor[clawMotor] = 60;
   	else if(vexRT[Btn5U])
   		motor[clawMotor] = -40;
   	else
   		motor[clawMotor] = 0;
  }
	StopAllTasks();
}
