#pragma systemFile

#ifndef FILE_mogoDriveControl_SEEN
#define FILE_mogoDriveControl_SEEN

//project wide forward PID tuning
float forwardP = 0.2;
float forwardI = 0.0002;
float forwardD = 250;

//project wide turning PID tuning
float turningP = 0.3;
float turningI = 0.0008;
float turningD = 350;

task mogoDriveControl(){//to control mobile goal transmission
	float turningPower = 0;
	float forwardPower = 0;

	//for setting transmission seperately
	float leftDriveValue[2];
	float rightDriveValue[2];

	//initialize values for mogo PID
	initializePIDLoop(mogoPID, 0.06, /*0.0001*/0, 0, 30, 500, mogoPot);//kI 0.00002

	initializePIDLoop(distanceDrivePID, forwardP, forwardI, forwardD, 1, 200, -1, true);//sensor value will be manually entered
	initializePIDLoop(angleDrivePID, turningP, turningI ,turningD , 1, 70, gyro, true);

	//enable all PID loops
	distanceDrivePID.enabled = true;
	angleDrivePID.enabled = true;
	mogoPID.enabled = true;

	while(true){
		//get drive values
		if(bIfiAutonomousMode){
			forwardPower = limit(calculatePIDValue(distanceDrivePID,(-SensorValue(driveEncoderL)+SensorValue(driveEncoderR))/2));
			turningPower = limit(calculatePIDValue(angleDrivePID));
			leftDriveValue[0] = forwardPower+turningPower;
			rightDriveValue[0] = forwardPower-turningPower;
		}
		else{
			leftDriveValue[0] = vexRT(Ch2)+trueSpeed(vexRT(Ch4));
			rightDriveValue[0] = vexRT(Ch2)-trueSpeed(vexRT(Ch4));
		}

		//calculate mobile goal PID values
		leftDriveValue[1] = rightDriveValue[1] = 1*limit(calculatePIDValue(mogoPID));
		/*leftDriveValue[1] = -1.25*limit(calculatePIDValue(mogoPID))

		rightDriveValue[1] = leftDriveValue[1];*/

		//sum drive values with mobile goal values
		leftDriveValue[1] += leftDriveValue[0];
		rightDriveValue[1] += rightDriveValue[0];

		//set independent motors
		motor[driveLF] = motor[driveLB] = leftDriveValue[0];
		motor[driveRF] = motor[driveRB] = rightDriveValue[0];

		//set transmisson motors to scaled values
		motor[driveLM] = leftDriveValue[1];
		motor[driveRM] = rightDriveValue[1];
		wait1Msec(12);
	}
}

void forward(float distance){
	angleDrivePID.kP = turningP*4;
	angleDrivePID.kI = turningI*2;
	angleDrivePID.kD = turningD*0;
	angleDrivePID.desiredValue += 0;
	distanceDrivePID.desiredValue += distance;
}

void turn(float angle){
	angleDrivePID.kP = turningP;
	angleDrivePID.desiredValue += (isRight? -1:1)*angle*10*6.7/9;
	distanceDrivePID.desiredValue += 0;
}

#endif
