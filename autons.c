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

	forward(450);
	delay(450);
	stackCone();

	forward(700);
	delay(500);
	distanceDrivePID.desiredValue = SensorValue(driveEncoderL) = SensorValue(driveEncoderR) = 0;
	forward(-80);
	delay(100);
	stackConeA();

	forward(-2500);
	stackConeB();
	//delay(10);
	liftPID.desiredValue+=500;
	delay(700);
	turn(45);
	delay(600);
	forward(-900);
	delay(800);
	turn(90);
	delay(400);
	forward(1500);
	delay(800);
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
