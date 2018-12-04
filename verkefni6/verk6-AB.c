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
#pragma config(Sensor, in3, lineFollowerLEFT,   sensorLineFollower)
#pragma config(Sensor, in4, lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in5, lineFollowerRIGHT,    sensorLineFollower)


#include "../GlobalFunctions/basic_movement.c"
const float resistance=0;

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
int distance_afram[4] = {200,100,50,40};
int distance_aftur[4] = {150,100,50,50};
int distance_snuavid[4] = {20,30,30,30};
bool direction_array[5] = {true,false,true,false,true};
bool beygja_inn_skila[4] = {true,true,true,false};
bool beygja_ut_skila[4] = {false,false,true,false};
task main_task(){
	for(int x=0;x<4;x++){
			follow_line_dist(distance_afram[x],resistance,true);
			search_line(direction_array[x]);
			follow_line_dist(40,resistance,true);
			arm(3700,-1);
			claw(-1);
			wait10Msec(200);
			claw(1);
			wait10Msec(100);
			arm(1700,1);
		//1700 3700
			search_line(true);
			follow_line_dist(distance_snuavid[x],resistance,true);
			search_line(direction_array[x+1]);
		 	follow_line_dist(distance_aftur[x]-10,resistance,true);
		 	search_line(beygja_inn_skila[x]);
		 	follow_line_dist(40,resistance,true);
		 	arm(2500,-1);
		 	wait10Msec(100);
		 	claw(-1);
		 	arm(1700,1);
		 	claw(1);
		 	search_line(true);
		 	follow_line_dist(30,resistance,true);
		 	search_line(beygja_ut_skila[x]);
	}


}
task main()
{
		StartTask(stopButton);
		StartTask(main_task);
		while(1==1){
		}

}
