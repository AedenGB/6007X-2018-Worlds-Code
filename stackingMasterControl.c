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
			if(numCones>12){delay(400);}
			else if(numCones>10){delay(300);}
			else if(numCones>7){delay(200);}
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

void stackConeAutoloader(){
  liftPID.desiredValue = LIFT_DOWN_ON_AUTOLOADER_POSITION-150;
	clearTimer(T2);
	while(SensorValue(intakeSensor)==1){
		if(time1(T2)>500){
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			return;
		}
		wait1Msec(5);
	}
	delay(50);
	closeIntake();
	wait1Msec(50);
	fourBarUp();
	liftPID.desiredValue+=1000;
	liftPID.kP*=10;
	delay(500);
	liftPID.kP/=10;
	/*liftPID.desiredValue = LIFT_PLACING_CONE_ONE_POSITION+numCones*HEIGHT_PER_CONE-20;
	while(fabs(liftPID.error)>50){
		if(time1(T2)>500){
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			return;
		}
		wait1Msec(5);
	}*/
	openIntake();
}

void intakeMobileGoal(){
	if(mobileGoalIn){
		mobileGoalIn = false;
		fourBarUp();
		clearTimer(T3);
		liftPID.desiredValue = limit(LIFT_PLACING_CONE_ONE_POSITION + numCones*HEIGHT_PER_CONE + 500,LIFT_DOWN_POSITION,LIFT_TOP_POSITION-150);
		while(time1[T3]<800&&fabs(liftPID.error)>100){
			wait1Msec(10);
		}
		delay(300);
		mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
		if(numCones>4){
			delay(500);
			mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
			clearTimer(T3);
			while(SensorValue(mogoPot)>MOBILE_GOAL_VERTICAL_POSITION && time1[T3]<700){delay(10);}
			mogoPID.kD = 4;//5
			mogoPID.kP/=4;
			delay(1000);
			mogoPID.kP*=4;
			mogoPID.kD = 0;
		}
		else{
			delay(300);
			mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
			delay(500);
		}
		liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
		liftPID.kP/=2;
		if(!bIfiAutonomousMode){
			delay(500);
		}
		else{
			delay(150);
		}
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
			if(!inAutoloaderMode){
				liftPID.desiredValue = LIFT_READY_INTAKE_POSITION;
			}
			else{
				liftPID.desiredValue = LIFT_READY_INTAKE_AUTOLOADER_POSITION;
			}
			fourBarDown();
			openIntake();
		}
		else{
			mogoPID.desiredValue = MOBILE_GOAL_OUT_POSITION;
			liftPID.desiredValue = LIFT_READY_INTAKE_POSITION+700;
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
			if(inAutoloaderMode){
				stackConeAutoloader();
			}
			else{
				stackCone();
			}
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

		if(vexRT[Btn7D]==1){
			inAutoloaderMode = !inAutoloaderMode;
			while(vexRT[Btn5U]==1){wait1Msec(5);}
		}

	}
}
#endif
