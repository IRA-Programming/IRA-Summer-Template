#include "robot-config.h"
#include "vex.h"
#include "PID.h"
#include "arm.h"
#include "functions.h"
#include "autons.h"

using namespace vex;


void rightAuton() {

  drivePID(12);
  turnPID(90);
  turnPID(-90);
  drivePID(-12);


}



void leftAuton() {
  
  //Use functions to create an auton for the right side of the field

}

void skillsAuton() {
  
  //Use functions to create a programming skills routine
  
}


  


