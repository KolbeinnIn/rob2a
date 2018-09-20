void drive(float mul)
{
	motor[rightMotor] = (int)(mul * 127);
	motor[leftMotor] = (int)(mul * 127);
}
