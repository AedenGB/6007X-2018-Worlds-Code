#pragma systemfile

#ifndef FILE_Utilities_SEEN
#define FILE_Utilities_SEEN

void resetGyro(){//turn power to gyro off, and then turn back on again
	int port = gyro;
	SensorType[port] = sensorNone;
	wait1Msec(500);
	SensorType[port] = sensorGyro;
	wait1Msec(1500);
}

float resetArray(float *arr, float val = 0){//set all values in an array to one value
	for(int i = 0;i<sizeof(arr)/sizeof(float);i++){
		arr[i] = val;
	}
	return arr;
}

int resetArray(int *arr, int val = 0){//set all values in an array to one value
	for(int i = 0;i<sizeof(arr)/sizeof(int);i++){
		arr[i] = val;
	}
	return arr;
}

void printToDebug(float val){//formats integers to print to debug stream
	string str;
	sprintf(str, "%d", val);
	strcat(str, " ");
	writeDebugStreamLine(str);
}

float limit(float val, float min = -127.0, float max = 999999){//caps a value
	if(max == 999999){
		max = 127;
	}
	if(val>max){
		return max;
	}
	if(val<min){
		return min;
	}
	return val;
}

float trueSpeed(float val){//delinearizes drive values from the joystick
	return sgn(val)*(127*pow(fabs(val)/127,1.4));
}

#endif
