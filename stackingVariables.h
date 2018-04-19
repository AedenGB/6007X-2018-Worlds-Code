#pragma systemfile

#ifndef FILE_stackingVariables_SEEN
#define FILE_stackingVariables_SEEN

//number of cones in robot
int numCones = 0;

//mobile goal variables
bool hasMobileGoal = false;
bool mobileGoalIn = true;

//at autoloader intaking height
bool inAutoloaderMode = false;

//lift positions
const float LIFT_DOWN_POSITION = 0;
const float LIFT_TOP_POSITION = 100;
const float LIFT_READY_INTAKE_POSITION = 50;
const float LIFT_READY_INTAKE_AUTOLOADER_POSITION = 50;
const float LIFT_DOWN_ON_AUTOLOADER_POSITION = 50;
const float LIFT_PLACING_CONE_ONE_POSITION = 50;
const float HEIGHT_PER_CONE = 100;

//mobile goal positions
const float MOBILE_GOAL_OUT_POSITION = 2000;
const float MOBILE_GOAL_IN_POSITION = 100;

#endif
