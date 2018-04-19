#pragma systemFile

#ifndef FILE_mogoDriveControl_SEEN
#define FILE_mogoDriveControl_SEEN

//transmission variable
bool usingMogo = false;

//project wide PID tuning
float driveP = 1.0;
float driveI = 0.0005;
float driveD = 15;

//project wide forward PID tuning
float forwardP = 1.0;
float forwardI = 0.0005;
float forwardD = 15;

//project wide forward PID tuning
float turningP = 1.0;
float turningI = 0.0005;
float turningD = 15;

void initializePIDLoopsForLocking(){
	initializePIDLoop(leftDistanceDrivePID, driveP, driveI, driveD, 1, 1000, driveEncoderL);
	initializePIDLoop(rightAngleDrivePID, driveP, driveI ,driveD , 1, 1000, driveEncoderR);
}

void initializePIDLoopsForDriving(){
	initializePIDLoop(leftDistanceDrivePID, forwardP, forwardI, forwardD, 1, 1000, -1);//sensor value will be manually entered
	initializePIDLoop(rightAngleDrivePID, turningP, turningI ,turningD , 1, 1000, gyro);
}


task mogoDriveControl(){//to control mobile goal transmission
	float turningPower = 0;
	float forwardPower = 0;

	//for setting transmission seperately
	float leftDriveValue[2];
	float rightDriveValue[2];



	//initialize values for mogo PID
	initializePIDLoop(mogoPID, 0.05, 0.00002, 5, 10, 1000, mogoPot);


	while(true){
		if(usingMogo){//mobile goal mode | lock drive | run mobile goal PID
			//calculate drive PID values
			leftDriveValue[0] = limit(calculatePIDValue(leftDistanceDrivePID));
			rightDriveValue[0] = limit(calculatePIDValue(rightAngleDrivePID));

			//calculate mobile goal PID values
			leftDriveValue[1] = rightDriveValue[1] = -limit(calculatePIDValue(mogoPID));

			//sum drive values with mobile goal values
			leftDriveValue[1] += leftDriveValue[0];
			rightDriveValue[1] += rightDriveValue[0];

			//set independent motors
			motor[driveLF] =  motor[driveLB] = leftDriveValue[0];
			motor[driveRF] = motor[driveRB] = rightDriveValue[0];

			//set transmisson motors to scaled values
			motor[driveLM] = leftDriveValue[1];
			motor[driveRM] = leftDriveValue[1];

		}
		else{//driving mode | unlock drive | run mobile goal PID to hold in place
			//get drive values
			if(bIfiAutonomousMode){
				forwardPower = limit(calculatePIDValue(leftDistanceDrivePID,(SensorValue(driveEncoderL)+SensorValue(driveEncoderR))/2));
				turningPower = limit(calculatePIDValue(rightAngleDrivePID));
				leftDriveValue[0] = forwardPower+turningPower;
				rightDriveValue[0] = forwardPower-turningPower;
			}
			else{
				leftDriveValue[0] = vexRT(Ch2)+trueSpeed(vexRT(Ch4));
				rightDriveValue[0] = vexRT(Ch2)-trueSpeed(vexRT(Ch4));
			}

			//calculate mobile goal PID values
			leftDriveValue[1] = rightDriveValue[1] = -limit(calculatePIDValue(mogoPID));

			//sum drive values with mobile goal values
			leftDriveValue[1] += leftDriveValue[0];
			rightDriveValue[1] += rightDriveValue[0];

			//set independent motors
			motor[driveLF] = motor[driveLB] = leftDriveValue[0];
			motor[driveRF] = motor[driveRB] = rightDriveValue[0];

			//set transmisson motors to scaled values
			motor[driveLM] = leftDriveValue[1];
			motor[driveRM] = rightDriveValue[1];
		}
		wait1Msec(50);
	}
}

#endif
