void drive(float mul)
{
	// mul controls the speed and direction
	motor[rightMotor] = (int)(mul * 127);
	motor[leftMotor] = (int)(mul * 127);
}
