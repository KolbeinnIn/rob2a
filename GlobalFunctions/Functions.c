void drive(float dist, float mul)
{
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
	SensorValue[rightEncoder] = 0; // Reset the right encoder value so the robot doesn't go too far

	while(abs(SensorValue[leftEncoder]) < dist || abs(SensorValue[rightEncoder]) < dist)
	{
		// mul controls the speed and direction
		motor[leftMotor] = (int)(mul * 122); // left motor 5 less because of power difference
		motor[rightMotor] = (int)(mul * 127);
	}

	// Stop the motors
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;

	writeDebugStreamLine("Left encoder value: %d", SensorValue[leftEncoder]);
}

// dir 1 (default) turns right, -1 turns left
void turn(int deg, float dir = 1)
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	while((abs(SensorValue[rightEncoder]) + abs(SensorValue[leftEncoder])) / 2 < deg * 2)
	{
		motor[rightMotor] = dir * -127;
		motor[leftMotor] = dir * 122;
	}

	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}

task stopButton()
{
	while(SensorValue[touchSensor] == 0 && vexRT[Btn7L] == 0){}
	StopAllTasks();
}

task holdArm()
{
	int initial = SensorValue[potentiometer];

	while(true)
	{
		while(SensorValue(potentiometer) == 0)
			motor[armMotor] = 30;

		motor[armMotor] = 0;
	}
}
