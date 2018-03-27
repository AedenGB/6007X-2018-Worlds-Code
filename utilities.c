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

void printToDebug(float val){//formats integers to print to debug stram
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

/*float scaleTo(float *values, float scale = 127){//take two numbers, and make them both under 127 while presering relative size and sign
	 if(scale<=0){//scales <=0 dont make sense
	   values[0] = 0;
	   values[1] = 0;
	 }
   else if(fabs(values[0]) <= scale && fabs(values[1]) <=scale){}//if both values are within the scale range, we don't need to do anything
   else if(fabs(values[0]) > fabs(values[1])){//first value determining factor (larger)
     values[1] = scale/fabs(values[0])*values[1];//scale second value
     values[0] = scale*sgn(values[0]);//limit first value
   }
   else {//second value determining factorn(larger)
     values[0] = scale/fabs(values[1])*values[0];//scale first value
     values[1] = scale*sgn(values[1]);//limit second vale
   }
   return values;
}*/

float scaleTo(float *values, float scale = 127.0){//take two numbers, and make them both under 127 while presering relative size and sign
	 /*if(scale<=0){//scales <=0 dont make sense
	   values[0] = 0;
	   values[1] = 0;
	 }
   else if(fabs(values[0]) >= scale && fabs(values[0]) >= fabs(values[1])){//first value determining factor (larger)
     values[1] = scale/fabs(values[0])*values[1];//scale second value
     values[0] = scale*sgn(values[0]);//limit first value
   }
   else if(fabs(values[1]) >= scale && fabs(values[1]) >= fabs(values[0])){//first value determining factor (larger)
     values[0] = scale/fabs(values[1])*values[0];//scale second value
     values[1] = scale*sgn(values[1]);//limit first value
   }*/
   return values;
}

#endif
