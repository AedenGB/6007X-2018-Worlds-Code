#pragma systemFile

#ifndef FILE_autons_SEEN
#define FILE_autons_SEEN

void fourConesIn20(){
	numCones = 0;
	liftPID.desiredValue = LIFT_READY_INTAKE_POSITION+100;
	delay(200);
	mobileGoalIn = false;
	mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
	delay(450);
	forward(1700);
	wait1Msec(1500);
	liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
	intakeMobileGoal();
	stackCone();
	forward(420);
	delay(500);

	numCones = 1;
	stackCone();
	forward(550);
	delay(550);
	liftPID.desiredValue = LIFT_DOWN_POSITION-150;
	clearTimer(T2);
	while(SensorValue(intakeSensor)==1){
		if(time1(T2)>500){
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			break;
		}
		wait1Msec(5);
	}
	closeIntake();
	wait1Msec(50);
	liftPID.desiredValue+=1000;
	forward(-2200);
	delay(10);
	numCones = 3;
	stackCone();

	liftPID.desiredValue+=500;
	delay(1200);
	turn(45);
	delay(500);
	forward(-970);
	delay(800);
	turn(90);
	delay(500);
	forward(1200);
	delay(1000);
	numCones = 4;
	intakeMobileGoal();
	forward(-1000);
	/*turn(-180);
	delay(1000);
	distanceDrivePID.desiredValue = SensorValue(driveEncoderL) = SensorValue(driveEncoderR) = SensorValue(gyro) = angleDrivePID.desiredValue = 0;
	intakeMobileGoal();
	forward(-500);*/
}
#endif
