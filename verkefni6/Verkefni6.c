#pragma config(Motor,  port4, leftMotor,    tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port6, rightMotor,   tmotorVex269, openLoop)
#pragma config(Motor,  port5, armMotor,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port3, clawMotor,    tmotorVex269, openLoop, reversed)
#pragma config(Sensor, dgtl5,	leftEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,	rightEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, touchSensor, sensorTouch)
#pragma config(Sensor, in1, potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1, sonarSensor,  sensorSONAR_cm)
#pragma config(Sensor, in2, lightSensor,  sensorReflection)
#pragma config(Sensor, in3, lineLeft,   sensorLineFollower)
#pragma config(Sensor, in4, lineMid,  sensorLineFollower)
#pragma config(Sensor, in5, lineRight,    sensorLineFollower)

#include "../GlobalFunctions/Functions.c"
const float speed = 1;
const float rotations = 1.5; // How many rotations for 0.5m
const int revolutions= 360;
const int sMainLine = 12;
float goalDist = 0;


void followDrive(int deg, float mSpeed, float dist, int sonarDist){
	SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
	SensorValue[rightEncoder] = 0;
	sonarDist += 5;
	dist *= 2;

	//while((abs(SensorValue[rightEncoder]) + abs(SensorValue[leftEncoder])) / 2 < dist){
	while(abs(SensorValue[rightEncoder]) < dist){
			if (dist == 0){
				break;
			}
			followLine();
	}

	while (true){
		if (SensorValue[sonarSensor] <= sonarDist - 2){
			motor[leftMotor] = -40;
			motor[rightMotor] = -40;
		}
		else if (SensorValue[sonarSensor] >= sonarDist + 2){
			motor[leftMotor] = 40;
			motor[rightMotor] = 40;
		}
		else
			break;
	}

	turn(15, mSpeed);

	do {
		turn(5, mSpeed);
	} while(!findLine());
}

void box(int deg){
		SensorValue[leftEncoder] = 0; // Reset the left encoder value so the robot doesn't go too far
		SensorValue[rightEncoder] = 0;
		while((abs(SensorValue[rightEncoder]) + abs(SensorValue[leftEncoder])) / 2 < 216){
			followLine();
		}
		wait1Msec(100);
		motor[leftMotor] = -40; //back up for a bit
		motor[rightMotor] = -40;
		wait1Msec(200);
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		turn(200,0.7);
		followDrive(deg, 0.7, 0, 74);
}

task main()
{
	StartTask(stopButton);
	//StartTask(holdArm);
	//StartTask(stopWhenDark);
	while (true){
		//writeDebugStreamLine("%d", SensorValue(sonarSensor));

		goalDist = (rotations * 2 * revolutions);
		followDrive(90, speed, goalDist, 15); //drive 2m, turn 90 degrees right

		goalDist = (rotations * 0.5 * revolutions);
		followDrive(180,speed,goalDist, 33); //drive 0.5m, turn 180 degrees right
		followDrive(90,-speed,goalDist, 74); //drive 0.5m, turn 90 degrees left

		goalDist = (rotations * 1.5 * revolutions);
		followDrive(90,speed,goalDist, 66); //drive 1.5m, turn 90 right

		box(-90); //first drop

		goalDist = (rotations * 1 * revolutions); //
		followDrive(90, -speed, goalDist, 62); //drive 1m, turn 90 degrees left

		goalDist = (rotations * 0.5 * revolutions);
		followDrive(190,speed,goalDist, 33); //drive 0.5m, turn 180 degrees right
		followDrive(90,speed,goalDist, 74); //drive 0.5m, turn 90 degrees right

		goalDist = (rotations * 1 * revolutions); //
		followDrive(90, speed, goalDist, 66); //drive 1m, turn 90 degrees right

		box(-90); //second drop

		goalDist = (rotations * 0.5 * revolutions);
		followDrive(90,speed,goalDist, 111); //drive 0.5m, turn 90 degrees right
		followDrive(190,speed,goalDist, 38); //drive 0.5m, turn 180 degrees right
		followDrive(90, -speed, goalDist, 74); //drive 0.5m turn 90 degrees left
		followDrive(90, speed, goalDist, 66);//drive 0.5m turn 90 degrees right

		box(90);




		/*
		writeDebugStreamLine("Left: %d", SensorValue[lineLeft]);
		writeDebugStreamLine("Mid: %d", SensorValue[lineMid]);
		writeDebugStreamLine("Right: %d", SensorValue[lineRight]);
		*/
		StopAllTasks();
	}
}
