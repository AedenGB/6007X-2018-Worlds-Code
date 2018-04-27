#pragma systemFile

#ifndef FILE_stackingMasterControl_SEEN
#define FILE_stackingMasterControl_SEEN

void stackCone(){
	if(SensorValue(intake) == 1){
	  liftPID.desiredValue = LIFT_DOWN_POSITION-150;
		clearTimer(T2);
		while(SensorValue(intakeSensor)==1){
			if(time1(T2)>500){
				liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
				//numCones--;
				return;
			}
			wait1Msec(5);
		}
		//delay(500);
		delay(50);
		closeIntake();
		wait1Msec(50);

		if(numCones<=1){
			liftControlMode = power;
			setLift(127);
			liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION+numCones*HEIGHT_PER_CONE+70;
			while(fabs(liftPID.desiredValue-SensorValue(liftPot))>100){
				wait1Msec(5);
			}
			fourBarUp();
		 	liftControlMode = position;
		}
		else{
			liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION+(numCones+1)*HEIGHT_PER_CONE-120;
			liftPID.kP*=7;
			fourBarUp();
			while(fabs(liftPID.error)>100){
				wait1Msec(5);
			}
			liftPID.kP/=7;
			wait1Msec(90+numCones*10);
			if((numCones)>10){delay(300);}
		}
	}
	else{
		liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION+(numCones+1)*HEIGHT_PER_CONE-20;
		delay(500);
	}

	wait1Msec(10);
	liftPID.desiredValue -=500;
	wait1Msec(200);
	openIntake();
	wait1Msec(40);
	liftPID.desiredValue+=1000;
	liftControlMode = power;
	setLift(127);
	wait1Msec(80+5*numCones);
	liftControlMode = position;
	wait1Msec(170);
	fourBarDown();
	wait1Msec(90);
	liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
	numCones++;

	liftPID.kP = liftkP;
}

void intakeMobileGoal(){
	if(mobileGoalIn){
		mobileGoalIn = false;
		fourBarUp();
		liftPID.desiredValue = limit(LIFT_PLACING_CONE_ONE_POSITION + numCones*HEIGHT_PER_CONE + 500,LIFT_DOWN_POSITION,LIFT_TOP_POSITION);
		while(fabs(liftPID.error)>100){
			wait1Msec(10);
		}
		delay(300);
		mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
		if(numCones>3){
			delay(400);
			mogoPID.kD = 3;
			delay(1000);
			mogoPID.kD = 0;
		}
		else{
			delay(500);
		}
		liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
		liftPID.kP/=2;
		delay(500);
		liftPID.kP*=2;
		/*if(numCones>1){
			//go down on and grab top cone
			wait1Msec(50);
	 		liftControlMode = power;
	 		clearTimer(T1);
	 		setLift(-40);
	 		wait1Msec(500);
	 		setLift(-5);
	 		closeIntake();
		}*/
	}
	else{
		fourBarUp();
		if(!bIfiAutonomousMode){
			liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION + 7*HEIGHT_PER_CONE + 400;
		}
		mobileGoalIn = true;
		mogoPID.desiredValue = MOBILE_GOAL_IN_POSITION;
		wait1Msec(500);
		if(!bIfiAutonomousMode){
			fourBarDown();
		}
		delay(150);
	}
}

task stackingMasterControl(){//controls master functions of stacking
	startTask(liftControl);
	startTask(mogoDriveControl);
	while(true){
		numCones = limit(numCones, 0, 17);
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

		//if decrement stack height pressed, increment
		if(vexRT[Btn5U]==1){
			numCones++;
			while(vexRT[Btn5U]==1){wait1Msec(5);}
		}
		//if increment stack height pressed, decrement
		else if(vexRT[Btn5D]==1){
			numCones--;
			while(vexRT[Btn5D]==1){wait1Msec(5);}
		}
		wait1Msec(30);

		//if autoloader stack toggle pressed, toggle autoloader mode



	}
}
#endif
