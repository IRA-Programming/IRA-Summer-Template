#include "vex.h"
#include "auton-selector.h"
#include "robot-config.h"
#include "functions.h"

using namespace vex;

// Defined in main.cpp - lets us trigger the auton routine from the selector
void autonomous(void);

// Defined in main.cpp - true while an auton is running so driver control stands down
extern bool inauton;

// Wrapper so the auton routine can run in its own task alongside the countdown
int runAutonTask() {
  autonomous();
  return 0;
}

int selectedAuton = 0;

const std::string autonNames[] = { "Right Auton", "Class Auton", "Skills", "Left Auton"};
const int autonCount = 4;

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

  // Run the auton in its own task while we show the 15-second auton-period
  // countdown. Driver control stays locked out (inauton) until the count hits 0.
  inauton = true;
  vex::task autonTask(runAutonTask);

  for (int t = 15; t >= 0; t--) {
    Controller.Screen.clearLine(3);
    Controller.Screen.setCursor(3, 1);
    Controller.Screen.print("Auton %d", t);
    if (t > 0) {
      wait(1, sec);
    }
  }

  // Auton period over - stop the routine and hand control back to the driver
  autonTask.stop();
  stopDT();
  inauton = false;

  Controller.Screen.clearLine(3);
}