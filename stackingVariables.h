#pragma systemfile

#ifndef FILE_stackingVariables_SEEN
#define FILE_stackingVariables_SEEN

//number of cones in robot
int numCones = 0;

//mobile goal variables
bool mobileGoalIn = true;

//at autoloader intaking height
bool inAutoloaderMode = false;

//lift positions
const float LIFT_DOWN_POSITION = 2000;
const float LIFT_TOP_POSITION = 4090;
const float LIFT_READY_INTAKE_POSITION = 2300;
const float LIFT_READY_INTAKE_AUTOLOADER_POSITION = 2750;
const float LIFT_DOWN_ON_AUTOLOADER_POSITION = 2400;
const float LIFT_PLACING_CONE_ONE_POSITION = 2200;
const float HEIGHT_PER_CONE = 110;

//mobile goal positions
const float MOBILE_GOAL_OUT_POSITION = 1640;
const float MOBILE_GOAL_IN_POSITION = 3520;
const float MOBILE_GOAL_VERTICAL_POSITION = 2600;

#endif
