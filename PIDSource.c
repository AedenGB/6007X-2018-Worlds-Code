 #pragma systemFile

#ifndef FILE_PID_SEEN
#define FILE_PID_SEEN

enum operation{plus = 0, times = 1, divided

struct PIDSource{//holds all the values for a PID loop
	string operationsAndPorts
}

//initialize atttributes to selected values
void initializePIDLoop(struct PIDLoop this){
}

//returns motorValue for given PID loop struct
float get(struct PIDLoop this){

}
#endif
