#pragma config(Motor, port6, rightMotor, tmotorNormal, openLoop)
#pragma config(Motor, port4, leftMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor, port5, armMotor, tmotorNormal, openLoop)

static int timePer50 = 965; // The time it takes (in ms) to go about 50cm
int power = 127;

void drive(int mul)
{
	motor[leftMotor] = mul * power;
	motor[rightMotor] = mul * power;
}

void driveSuicide(int *i){
	drive(1);

	writeDebugStreamLine("%d", *i);
	writeDebugStreamLine("%d", timePer50 * (*i+1));

	wait1Msec(timePer50 * (*i + 1));

	drive(-1);

	wait1Msec(timePer50 * (*i + 1));
}

task main()
{
	motor[armMotor] = 0;

	for (int i = 0; i < 5; i++)
	{
		driveSuicide(&i);

		drive(0);

		wait1Msec(200);
	}
}
