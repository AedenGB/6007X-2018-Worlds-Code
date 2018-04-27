#pragma systemfile

#ifndef FILE_Utilities_SEEN
#define FILE_Utilities_SEEN

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
	writeDebugStream(str);
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
