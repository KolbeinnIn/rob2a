void drive(float mul)
{
	// mul controls the speed and direction
	motor[leftMotor] = (int)(mul * 127);
	motor[rightMotor] = (int)(mul * 127);
}

// dir 1 (default) turns left, -1 turns right
void turn(int deg, int dir = 1)
{
	SensorValue[leftEncoder] = 0;

	while(abs(SensorValue[leftEncoder]) < deg * 2.75)
	{
		motor[rightMotor] = dir * 127;
		motor[leftMotor] = dir * -127;
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
