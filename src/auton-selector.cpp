#include "vex.h"
#include "auton-selector.h"
#include "robot-config.h"

using namespace vex;

// Defined in main.cpp - lets us trigger the auton routine from the selector
void autonomous(void);

int selectedAuton = 0;

const std::string autonNames[] = { "Right Auton", "Class Auton", "Skills"};
const int autonCount = 3;

int getSelectedAuton() {
  return selectedAuton;
  //make sure to press right auton//
}

void displayAutonSelector() {

  Controller.Screen.clearLine(3);
  Controller.Screen.setCursor(3, 1);
  Controller.Screen.print("Auton: %s", autonNames[selectedAuton].c_str());

  while (true) {
  
    if (Controller.ButtonLeft.pressing()) {
      selectedAuton = (selectedAuton - 1 + autonCount) % autonCount;
      while(Controller.ButtonLeft.pressing()) {
        wait(10, msec);
      }
      Controller.Screen.clearLine(3);
      Controller.Screen.setCursor(3, 1);
      Controller.Screen.print("Auton: %s", autonNames[selectedAuton].c_str());
    }

    if (Controller.ButtonRight.pressing()) {
      selectedAuton = (selectedAuton + 1) % autonCount;
      while(Controller.ButtonRight.pressing()) {
        wait(10, msec);
      }
      Controller.Screen.clearLine(3);
      Controller.Screen.setCursor(3, 1);
      Controller.Screen.print("Auton: %s", autonNames[selectedAuton].c_str());
    }

    if (Controller.ButtonX.pressing()) {
      vex::task::sleep(600); //hold down X for 0.6 seconds to select
      if (Controller.ButtonX.pressing()) {
        Controller.rumble("..");
        break;
      }
    }

    

    wait(20, msec);
  }

  // Holding X selected the auton - now count down and start it automatically
  for (int i = 3; i > 0; i--) {
    Controller.Screen.clearLine(3);
    Controller.Screen.setCursor(3, 1);
    Controller.Screen.print("Starting in %d...", i);
    wait(1, sec);
  }

  Controller.Screen.clearLine(3);
  Controller.Screen.setCursor(3, 1);
  Controller.Screen.print("Auton running!");

  autonomous();

  Controller.Screen.clearLine(3);
}