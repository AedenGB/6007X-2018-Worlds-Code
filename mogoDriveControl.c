#pragma systemFile

#ifndef FILE_mogoDriveControl_SEEN
#define FILE_mogoDriveControl_SEEN

//transmission variable
bool usingMogo = false;

task mogoDriveControl(){//to control mobile goal transmission
	//task wide PID tuning
	float driveP = 1.0;
	float driveI = 0.0005;
	float driveD = 1;
	//for setting transmission seperately
	float leftDriveValue[2];
	float rightDriveValue[2];
	//initialize drive PID structs
	struct PIDLoop leftDrivePID;
	struct PIDLoop rightDrivePID;
	initializePIDLoop(leftDrivePID, driveP, driveI, driveD, 1, 1000, driveEncoderL);
	initializePIDLoop(rightDrivePID, driveP, driveI ,driveD , 1, 1000, driveEncoderR);
	//initialize mogo PID structs
	struct PIDLoop mogoPID;
	initializePIDLoop(mogoPID, 0.1, 0.00002, 5, 100, 1000, mogoPot);
	while(true){
		leftDrivePID.desiredValue = SensorValue(leftDrivePID.sensorPort);
		rightDrivePID.desiredValue = SensorValue(leftDrivePID.sensorPort);
		if(usingMogo||true){//mobile goal mode | lock drive | run mobile goal PID
			//calculate drive PID values
			leftDriveValue[0] = limit(calculatePIDValue(leftDrivePID));
			rightDriveValue[0] = limit(calculatePIDValue(rightDrivePID));
			//calculate mobile goal PID values
			leftDriveValue[1] = rightDriveValue[1] = -limit(calculatePIDValue(mogoPID));
			//sum drive values with mobile goal values
			/*leftDriveValue[1] += leftDriveValue[0];
			rightDriveValue[1] += rightDriveValue[0];
			//scale values to 127, to use ratio instead of actual values
			leftDriveValue = scaleTo(leftDriveValue);
			rightDriveValue = scaleTo(rightDriveValue);*/
			//set independent motors
			motor[driveLF] =  motor[driveLB] = leftDriveValue[0];
			motor[driveRF] = motor[driveRB] = rightDriveValue[0];
			//set transmisson motors to scaled values
			motor[driveLM] = leftDriveValue[1];
			motor[driveRM] = leftDriveValue[1];

		}
		else{//driving mode | unlock drive | run mobile goal PID to hold in place
			//get drive values
			leftDriveValue[0] = vexRT(Ch2)+trueSpeed(vexRT(Ch4));
			rightDriveValue[0] = vexRT(Ch2)-trueSpeed(vexRT(Ch4));
			//calculate mobile goal PID values
			leftDriveValue[1] = rightDriveValue[1] = limit(calculatePIDValue(mogoPID));
			//sum drive values with mobile goal values
			leftDriveValue[1] += leftDriveValue[0];
			rightDriveValue[1] += rightDriveValue[0];
			//scale values to 127, to use ratio instead of actual values
			leftDriveValue = scaleTo(leftDriveValue);
			rightDriveValue = scaleTo(rightDriveValue);
			//set independent motors
			motor[driveLF] =  motor[driveLB] = leftDriveValue[0];
			motor[driveRF] = motor[driveRB] = rightDriveValue[0];
			//set transmisson motors to scaled values
			motor[driveLM] = leftDriveValue[1];
			motor[driveRM] = leftDriveValue[1];
		}
		wait1Msec(50);
	}
}

#endif
