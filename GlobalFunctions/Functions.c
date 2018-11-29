/* GLOBALS */
int running = 1;
task verk4();
void drive(float dist, float mul)
{
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
	SensorValue[rightEncoder] = 0; // Reset the right encoder value so the robot doesn't go too far

	while(abs(SensorValue[leftEncoder]) < dist || abs(SensorValue[rightEncoder]) < dist || dist == -1)
	{
		// mul controls the speed and direction
		motor[leftMotor] = (int)(mul * 127); // left motor 5 less because of power difference
		motor[rightMotor] = (int)(mul * 127);
	}

	// Stop the motors
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

// dir 1 (default) turns right, -1 turns left
void turn(int deg, float dir = 1)
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	while((abs(SensorValue[rightEncoder]) + abs(SensorValue[leftEncoder])) / 2 < deg * 1.8)
	{
		motor[rightMotor] = dir * -127;
		motor[leftMotor] = dir * 127;
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
	//writeDebugStreamLine("start holdArm");
	while(true)
	{
		while(SensorValue(potentiometer) < 640)
			motor[armMotor] = 50;

		motor[armMotor] = 0;
	}
}

task armControl()
{
	while(true)
	{
		wait1Msec(1000);
	}
}

task stopArmControl()
{
	StartTask(armControl);

	const int min = 640;
	const int max = 2400;

	while(true)
	{
		int potent = SensorValue[potentiometer];

		if(potent > max)
		{
			StopTask(armControl);

			while(potent > max - 50)
			{
				motor[armMotor] = -50;
				potent = SensorValue[potentiometer];
			}

			motor[armMotor] = 0;
			StartTask(armControl);
		}
		else if(potent < min)
		{
			StopTask(armControl);
			wait1Msec(1000);
			StartTask(armControl);
		}
	}
}

task stopWhenDark(){
	while (true){
		//writeDebugStreamLine("%d", SensorValue[lightSensor]);
		if (SensorValue[lightSensor] > 270){
			StopTask(verk4);
			drive(0,0);
		}
		else
			StartTask(verk4);
	}
}
void followLine(){
	const int speed = 60;
	const int threshold = 1419;
	//while (true){
		if(SensorValue(lineLeft) > threshold)
		    {
		      // counter-steer right:
		      motor[leftMotor]  = -speed;
		      motor[rightMotor] = speed;
		    }
		    // CENTER sensor sees dark:

		    if(SensorValue(lineMid) > threshold)
		    {
		      // go straight
		      motor[leftMotor]  = speed;
		      motor[rightMotor] = speed;
		    }
		    // LEFT sensor sees dark:
		    if(SensorValue(lineRight) > threshold)
		    {
		      // counter-steer left:
		      motor[leftMotor]  = speed;
		      motor[rightMotor] = -speed;
		    }
  //}
}

bool findLine()
{
	const int threshold = 1419;

	if(SensorValue(lineMid) > threshold)
	{
		return true;
	}

	return false;
}
