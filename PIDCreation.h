#pragma systemfile

#ifndef FILE_PIDCreation_SEEN
#define FILE_PIDCreation_SEEN

//create drive PID loops
struct PIDLoop distanceDrivePID;
struct PIDLoop angleDrivePID;

//create mogo PID
struct PIDLoop mogoPID;

//create lift PID

struct PIDLoop liftPID;

#endif
