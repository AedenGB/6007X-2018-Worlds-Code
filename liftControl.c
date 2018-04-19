#pragma systemFile

#ifndef FILE_liftControl_SEEN
#define FILE_liftControl_SEEN

task liftControl(){//to control mobile goal transmission
	//initialize values
	initializePIDLoop(liftPID, 0.05, 0, 0, 10, 1000, liftPot);

	//continuously set lift motors to calculated values
	while(true){
		setLift(calculatePIDValue(liftPID));
		wait1Msec(50);
	}
}
#endif
