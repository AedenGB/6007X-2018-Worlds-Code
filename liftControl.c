#pragma systemFile

#ifndef FILE_liftControl_SEEN
#define FILE_liftControl_SEEN

enum controlMode{position = 0, power = 1};
enum controlMode liftControlMode = position;

const float liftkP = 0.1;
const float liftkI = 0.0001;
const float liftkD = 130;

task liftControl(){//to control mobile goal transmission
	//initializePIDLoop(liftPID, 0.05, 0.0002, 8 , 30, 250, liftPot);
	initializePIDLoop(liftPID, liftkP, liftkI, liftkD, 30, 250, liftPot);
	//initializePIDLoop(liftPID, 0.07, 0.000175, 4 , 30, 250, liftPot);
	//continuously set lift motors to calculated values
	while(true){
		if(liftControlMode == position){
			liftPID.enabled = true;
			setLift(calculatePIDValue(liftPID));
		}
		else{
			liftPID.enabled = false;
		}
		wait1Msec(12);
	}
}


#endif
