#include "vex.h"
#include "auton-selector.h"
#include "robot-config.h"
#include "functions.h"

using namespace vex;

// Defined in main.cpp - lets us trigger the auton routine from the selector
void autonomous(void);

// Defined in main.cpp - true while an auton is running so driver control stands down
extern bool inauton;

// Set true by the countdown task once the 15-second auton period has elapsed
bool autonCountdownDone = false;

// Runs in its own task: shows the 15-second auton-period countdown on the
// controller screen (screen only - no motor control) while the auton routine
// runs on the main thread.
int runCountdownDisplay() {
  for (int t = 15; t >= 0; t--) {
    Controller.Screen.clearLine(3);
    Controller.Screen.setCursor(3, 1);
    Controller.Screen.print("Auton %d", t);
    if (t > 0) {
      vex::task::sleep(1000);
    }
  }
  autonCountdownDone = true;
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

  // Lock out the driver, then run the auton routine on THIS thread (the proven
  // movement path) while the 15-second countdown ticks in a separate display task.
  inauton = true;
  autonCountdownDone = false;
  vex::task countdownTask(runCountdownDisplay);

  autonomous();

  // Keep the driver locked out until the 15-second countdown reaches 0
  while (!autonCountdownDone) {
    wait(20, msec);
  }

  // Auton period over - hand control back to the driver
  stopDT();
  inauton = false;

  Controller.Screen.clearLine(3);
}