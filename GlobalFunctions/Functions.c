void drive(float dist, float mul)
{
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far

	while(abs(SensorValue[leftEncoder]) < dist)
	{
		// mul controls the speed and direction
		motor[leftMotor] = (int)(mul * 122); // left motor 5 less because of power difference
		motor[rightMotor] = (int)(mul * 127);
	}

	writeDebugStreamLine("Left encoder value: %d", SensorValue[leftEncoder]);
}

// dir 1 (default) turns left, -1 turns right
void turn(int deg, int dir = 1)
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	while((abs(SensorValue[rightEncoder]) + abs(SensorValue[leftEncoder])) / 2 < deg * 2.75)
	{
		motor[rightMotor] = dir * 127;
		motor[leftMotor] = dir * -122;
	}

	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}

task stopButton()
{
	while(SensorValue[touchSensor] == 0){}

	writeDebugStreamLine("Takki: %d", SensorValue[touchSensor]);
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
