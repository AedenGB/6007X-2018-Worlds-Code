#pragma systemFile

#ifndef FILE_stackingMasterControl_SEEN
#define FILE_stackingMasterControl_SEEN

void stackCone(){
	liftPID.desiredValue = LIFT_DOWN_POSITION;
	clearTimer(T2);
	while(SensorValue(intakeSensor)==0){
		if(time1(T2)>0.3){
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			return;
		}
		wait1Msec(5);
	}
	liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION+numCones*HEIGHT_PER_CONE;
	while(fabs(liftPID.error)>50){
		delay(5);
	}
	fourBarUp();
	delay(100);
	openIntake();
	delay(200);
	fourBarDown();
	delay(300);
	liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
}

void intakeMobileGoal(){
	//get ready to use mogo
	initializePIDLoopsForLocking();
	leftDistanceDrivePID.desiredValue = SensorValue(leftDistanceDrivePID.sensorPort);
	rightAngleDrivePID.desiredValue = SensorValue(rightAngleDrivePID.sensorPort);
	usingMogo = true;
	if(mobileGoalIn){
			//raise lift
			liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION + numCones*HEIGHT_PER_CONE + 100;
			while(fabs(liftPID.error) > 50){
				wait1Msec(5);
			}
			fourBarUp();
		if(numCones>1){
			//go down on and grab top cone
			wait1Msec(50);
	 		liftControlMode = power;
	 		clearTimer(T1);
	 		setLift(-40);
	 		delay(500);
	 		setLift(-15);
	 		closeIntake();
		}

 		//put mobile goal out
 		mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
 		while(SensorValue(mogoPot)<MOBILE_GOAL_VERTICAL_POSITION){
 			wait1Msec(5);
 		}
 		fourBarDown();
 		while(fabs(mogoPID.error)<50){
 			wait1Msec(5);
 		}
 		delay(200);

 		//get off stack
 		openIntake();
 		fourBarUp();
 		delay(10);
 		liftControlMode = position;
	}
	else{
		//get lift out of the way
		liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION + 5*HEIGHT_PER_CONE + 100;
		mogoPID.desiredValue = MOBILE_GOAL_IN_POSITION;
		//wait till mobile goal intake is in
		while(fabs(mogoPID.error)>50){
 			wait1Msec(5);
 		}
 		fourBarDown();
	}
	usingMogo = false;
	initializePIDLoopsForDriving();
}

task stackingMasterControl(){//controls master functions of stacking
	while(true){
		//if has a mobile goal, get ready to intake a cone
		if(mobileGoalIn){
			mogoPID.desiredValue = MOBILE_GOAL_IN_POSITION;
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			fourBarDown();
			openIntake();
		}
		else{
			mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			fourBarUp();
			openIntake();
		}

		//if mobile goal button pressed, intake/outtake mogo
		if(vexRT[Btn6D]==1){
			intakeMobileGoal();
			numCones = 0;
		}

		//if has mogo and stack button pressed, stack cone
		if(vexRT[Btn6U]==1 && mobileGoalIn){
			stackCone();
		}

		//if decrement stack height pressed, decrement
		if(vexRT[Btn5U]==1){
			numCones = limit(numCones+1,0,15);
			while(vexRT[Btn5U]==1){delay(5);}
		}
		//if increment stack height pressed, increment
		else if(vexRT[Btn5D]==1){
			numCones = limit(numCones-1,0,15);
			while(vexRT[Btn5D]==1){delay(5);}
		}
		delay(30);

		//if autoloader stack toggle pressed, toggle autoloader mode



	}
}
#endif
