#pragma systemfile

#ifndef FILE_subsystemFunctions_SEEN
#define FILE_subsystemFunctions_SEEN

//set lift motors to power
void setLift(float val){
	motor[liftLB] = motor[liftLT] = motor[liftRB] = motor[liftRT] = val;
}

//closes intake clip
void closeIntake(){
	SensorValue(intake) = 1;
}

//opens intake clip
void openIntake(){
	SensorValue(intake) = 0;
}

//puts 4 bar down
void fourBarDown(){
	SensorValue(fourBarL) = SensorValue(fourBarR) = 1;
}

//lifts 4 bar
void fourBarUp(){
	SensorValue(fourBarL) = SensorValue(fourBarR) = 0;
}


#endif
