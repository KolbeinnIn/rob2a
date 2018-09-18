#pragma config(Motor, port6, rightMotor, tmotorNormal, openLoop)
#pragma config(Motor, port4, leftMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor, port5, armMotor, tmotorNormal, openLoop)

static int timePer50 = 965; // The time it takes (in ms) to go about 50cm
//static int timePer50 = 100; // The time it takes (in ms) to go about 50cm

task main()
{
	motor[armMotor] = 0;

	for (int i = 0; i < 5; i++)
	{
		motor[rightMotor] = 127;
		motor[leftMotor] = 127;

		writeDebugStreamLine("%d", i);
		writeDebugStreamLine("%d", timePer50*(i+1));

		wait1Msec(timePer50 * (i + 1));

		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(200);

		motor[rightMotor] = -127;
		motor[leftMotor] = -127;

		wait1Msec(timePer50 * (i + 1));

		motor[rightMotor] = 0;
		motor[leftMotor] = 0;

		wait1Msec(200);
	}
}
