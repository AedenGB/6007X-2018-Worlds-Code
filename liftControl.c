#pragma systemFile

#ifndef FILE_liftControl_SEEN
#define FILE_liftControl_SEEN

enum controlMode{position = 0, power = 1};
enum controlMode liftControlMode = position;

task liftControl(){//to control mobile goal transmission
	//initialize values
	initializePIDLoop(liftPID, 0.05, 0, 0, 10, 1000, liftPot, true);

	//continuously set lift motors to calculated values
	while(true){
		if(liftControlMode == position){
			liftPID.enabled = true;
			setLift(calculatePIDValue(liftPID));
		}
		else{
			liftPID.enabled = false;
		}
		wait1Msec(50);
	}
}


#endif
