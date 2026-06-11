#include "robot-config.h"
#include "vex.h"
#include "PID.h"
#include "lift.h"
#include "functions.h"
#include "autons.h"

using namespace vex;


void rightAuton() {

  drivePID(12);
  turnPID(90);
  turnPID(-90);
  drivePID(-12);


}



void classAuton() {

  //Write your own auton here!

}

void skillsAuton() {
  
  //Use functions to create a programming skills routine
  
}


  


