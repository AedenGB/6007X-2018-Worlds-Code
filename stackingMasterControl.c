#pragma systemFile

#ifndef FILE_stackingMasterControl_SEEN
#define FILE_stackingMasterControl_SEEN

void stackCone(){
	liftPID.desiredValue = LIFT_DOWN_POSITION;
}

void intakeMobileGoal(){
	leftDistanceDrivePID.desiredValue = SensorValue(leftDistanceDrivePID.sensorPort);
	rightAngleDrivePID.desiredValue = SensorValue(rightAngleDrivePID.sensorPort);
	initializePIDLoopsForLocking();
	usingMogo = true;
	if(mobileGoalIn){
		liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION + numCones*HEIGHT_PER_CONE + 100;
		while(fabs(liftPID.error) > 50){
			wait1Msec(5);
		}
		fourBarUp();
		wait1Msec(50);

	}
	else{

	}
	initializePIDLoopsForDriving();
}

task stackingMasterControl(){//controls master functions of stacking
	while(true){
		//if has a mobile goal, get ready to intake a cone
		if(hasMobileGoal){
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			fourBarDown();
			openIntake();
		}
		else{
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
		if(vexRT[Btn6U]==1 && hasMobileGoal){
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
