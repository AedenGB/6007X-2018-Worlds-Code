void stackConeA(){
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
}
void stackConeB(){
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
