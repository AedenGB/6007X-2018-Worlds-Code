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
	forward(500);
	delay(400);

	numCones = 0;
	stackCone();
	forward(380);
	delay(370);
	numCones = 2;

	stackCone();
	forward(320);
	delay(330);
	numCones = 3;
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

	liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION+numCones*HEIGHT_PER_CONE-120;
	liftPID.kP*=7;
	fourBarUp();
	//forward(-2200);
	delay(500);
	stackCone();
	/*turn(45);
	delay(700);
	forward(-1000);
	delay(700);
	turn(90);
	delay(600);
	forward(800);
	delay(1000);
	intakeMobileGoal();
  forward(-1000);
  delay(500);*/
}
#endif
