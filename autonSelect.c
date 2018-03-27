#pragma systemFile

#ifndef FILE_AutonSelect_SEEN
#define FILE_AutonSelect_SEEN

//lcd button values
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

//lcd values
int isRight = 0;//auton selected and displayed
int autonType = 0;//auton selected and displayed
string batteryDisplay;
string autonDisplay;


void loadingScreen(){//loading animation
	displayLCDCenteredString(0,"loading");
  clearLCDLine(1);
	int i = 0;
  while(i<20*16){
  	i+=20;
  	delay(40);
  	setLCDPosition(1, i/20);
    displayNextLCDChar('.');
  }
}

void generateBatteryString(){//updates batteryDisplay to current battery level
	string mainBattery;
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0); //Build the value to be displayed
	strcat(batteryDisplay, "Battery : ");
	strcat(batteryDisplay, mainBattery);
}

void waitForPressLcd(){//wait for user to press a button
	generateBatteryString();
	while(nLCDButtons == 0){
		clearLCDLine(0);
		displayLCDCenteredString(1,batteryDisplay);
		wait1Msec(1);
	}
}

void waitForRelease(){//wait for all buttons to get released
	generateBatteryString();
	while(nLCDButtons != 0){
		clearLCDLine(0);
		displayLCDCenteredString(1,batteryDisplay);
		wait1Msec(1);
	}
}

void displayAuton(int auton){//display current selected auton
	sprintf(autonDisplay,"%sautons[auton]%s\n", "<", ">");
	displayLCDCenteredString(0,autonDisplay);
	waitForPressLcd();
	if (nLCDButtons == leftButton){
		waitForRelease();
		if(autonType == 0){
			autonType = sizeof(autons)-1;
		}
		else{
			autonType--;
		}
	}
	else if (nLCDButtons == rightButton){
		waitForRelease();
		if(autonType >= sizeof(autons)-1){
			autonType = 0;
		}
		else{
			autonType++;
		}
	}
}


task autonSelect(){
	//initialize lcd
	bLCDBacklight = true;
	clearLCDLine(1);
	clearLCDLine(0);
	//loop while center button not pressed
	while(nLCDButtons != centerButton){
		switch(isRight){
		case 0://no auton
			displayLCDCenteredString(0, "<none>");
			waitForPressLcd();
			if (nLCDButtons == leftButton){
				waitForRelease();
				isRight = 2;
			}
			else if (nLCDButtons == rightButton){
				waitForRelease();
				isRight++;
			}
			break;
		case 1://left
			displayLCDCenteredString(0, "<left>");
			waitForPressLcd();
			if (nLCDButtons == leftButton){
				waitForRelease();
				isRight--;
			}
			else if (nLCDButtons == rightButton){
				waitForRelease();
				isRight++;
			}
			break;
		case 2://right
			displayLCDCenteredString(0, "<right>");
			waitForPressLcd();
			if (nLCDButtons == leftButton){
				waitForRelease();
				isRight--;
			}
			else if (nLCDButtons == rightButton){
				waitForRelease();
				isRight = 0;
			}
			break;
		default:
			displayLCDCenteredString(0,"BOOM BOOM DEATH!");//error message if robot is dead
			isRight = 0;
			break;
		}
	}
  waitForRelease();
	if(isRight>0){
	  loadingScreen();
		while(nLCDButtons != centerButton){
			displayAuton(autonType);
		}
	}
	loadingScreen();
	displayLCDCenteredString(0, "Selected");
}
#endif
