#pragma config(Motor,  port4, leftMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorNormal, openLoop)
#pragma config(Motor,  port5, armMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3, clawMotor, tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)
#pragma config(Sensor, in1, potentiometer, sensorPotentiometer)

#include "../GlobalFunctions/Functions.c"

const int deadzone = 10;

//ATH!! connection virkadi aldrei thannig thessi kodi gaeti eda gaeti ekki virkad.
task main()
{
	//StartTask(stopButton);

	while(1 == 1)
  {
    //Driving controlled by left stick
    /*motor[rightMotor] = vexRT[Ch3];
    motor[leftMotor] = vexRT[Ch3];

    //Turning controlled by right stick
    int tmpRightStickX = vexRT[Ch1];
    writeDebugStreamLine("%d", tmpRightStickX);

    if(tmpRightStickX < -deadzone)
    {
    	motor[rightMotor] = tmpRightStickX;
    	motor[leftMotor] = -tmpRightStickX;
    }
    else if(tmpRightStickX > deadzone)
    {
    	motor[rightMotor] = -tmpRightStickX;
    	motor[leftMotor] = tmpRightStickX;
    }*/

    motor[rightMotor] = vexRT[Ch3] - vexRT[Ch4];
    motor[leftMotor] = vexRT[Ch3] + vexRT[Ch4];

    motor[armMotor] = vexRT[Ch2];

    if(vexRT[Btn6U])
    	motor[clawMotor] = 60;
   	else if(vexRT[Btn5U])
   		motor[clawMotor] = -40;
   	else
   		motor[clawMotor] = 0;
  }

	StopAllTasks();
}
