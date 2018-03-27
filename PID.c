 #pragma systemFile

#ifndef FILE_PID_SEEN
#define FILE_PID_SEEN

struct PIDLoop{//holds all the values for a PID loop
	float kP;
	float kI;
	float kD;
	float acceptableRange;
	float maxErrorI;
	int sensorPort;
	bool reverseSensor;
	float error;
	float desiredValue;
	float pVal;
	float iVal;
	float dVal;
	int oldErrorArr[50];
	float oldError;
	int oldTime;
	float timeChange;
	int writeCounter;
}

//initialize atttributes to selected values
void initializePIDLoop(struct PIDLoop this, float kP, float kI, float kD, float acceptableRange,
	float maxErrorI, int sensorPort, bool reverseSensor = false){
	this.kP = kP;
	this.kI = kI;
	this.kD = kD;
	this.acceptableRange = acceptableRange;
	this.maxErrorI = maxErrorI;
	this.sensorPort = sensorPort;
	this.reverseSensor = reverseSensor;
	this.error = 0;
	this.desiredValue = SensorValue(this.sensorPort);
	this.pVal = 0;
	this.iVal = 0;
	this.dVal = 0;
	this.oldError = 0;
	this.writeCounter = 0;
	this.oldTime = 0;
	this.timeChange = 0;
	this.writeCounter = 0;
}

//returns motorValue for given PID loop struct
float calculatePIDValue(struct PIDLoop this){
	//calculate delta time since last call
	do{
		if(this.timeChange==0){//if the do while loop came back, wait 1 mllis to get actual time change
			wait1Msec(1);
		}
		this.timeChange = nSysTime-this.oldTime;
		this.oldTime = nSysTime;
	}while(this.timeChange <= 0);
	//calculate error
	this.error = this.desiredValue-(this.reverseSensor?-1:1)*SensorValue[this.sensorPort];
	//set P value
	this.pVal = this.error;

	//subtract oldest value from I
	this.iVal -= this.oldErrorArr[this.writeCounter];

	//add newest value to I
	if(fabs(this.error)<this.maxErrorI){
		this.iVal += this.error*this.timeChange;
	}
	//calculate derivative
	this.dVal = -(this.oldError-this.error)/(float)this.timeChange;

	//set I to 0 if within acceptable range
	if(fabs(this.error)<this.acceptableRange){
		  resetArray(this.oldErrorArr);
			this.iVal = 0;
	}
	//set old error in circular array
	this.oldErrorArr[this.writeCounter] = this.error*this.timeChange;
	this.writeCounter %= (sizeof(this.oldErrorArr)/sizeof(this.oldErrorArr[0]))-1;
	this.writeCounter++;
	//set old error variable
	this.oldError = this.error;
	//return motor Value
	return this.pVal*this.kP + limit(this.iVal*this.kI,-50,50) + this.dVal*this.kD;
}
#endif
