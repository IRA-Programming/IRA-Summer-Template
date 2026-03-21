#include "autons.h"
#include "robot-config.h"
#include "vex.h"
#include "functions.h"
#include "PID.h"

using namespace vex;



//PID function for forwards/backwards motion
void drivePID(double targetInches, double kP, double kI, double kD) {

  setDTPosition(0); //reset encoders

  double error = targetInches;
  double integral = 0;
  double derivative = 0;

  double lastError = 0;
  double maxIntegral = 100;


  while (fabs(error) > 0.5) { //Keep running until you’re within 0.5 inches of your target
    
    double leftAvg = (LF.position(degrees) + LM.position(degrees) + LB.position(degrees)) / 3.0;
    double rightAvg = (RF.position(degrees) + RM.position(degrees) + RB.position(degrees)) / 3.0;

    double inchesTravelled = degreesToInches((leftAvg + rightAvg) / 2.0);

    error = targetInches - inchesTravelled;

    integral += error * 0.020; //add to the integral sum to sum up error over time

    // Anti-windup
    if (integral > maxIntegral) integral = maxIntegral;
    if (integral < -1 * maxIntegral) integral = -1 * maxIntegral;

    derivative = (error - lastError) / 0.020; //find the rate of change of the error over time
    lastError = error;

    double power = (kP * error) + (kI * integral) + (kD * derivative);

    // Clamp output
    if (power > 100) power = 100;
    if (power < -100) power = -100;

    spinDT(power * 0.7);

    task::sleep(20); // small loop delay
  }

  stopDT();
  Controller.Screen.print("done");
  Controller.Screen.print(targetInches);

}

//PID function for rotating clockwise (CW) or counterclockwise (CCW)
void turnPID(double targetAngle, double kP, double kI, double kD) {

  double dir = targetAngle / fabs(targetAngle);

  // Reset inertial rotation value
  InertialSensor.setRotation(0, degrees);

  // PID state
  double error = targetAngle;
  double integral = 0;
  double derivative = 0;
  double lastError = 0;
  const double maxIntegral = 100;

  targetAngle = fabs(targetAngle);

  // loop til we’re close
  while (fabs(error) > 2.0) {

    error = targetAngle - fabs(InertialSensor.rotation(degrees));
    integral += error * 0.020;

    if (integral >  maxIntegral) integral =  maxIntegral;
    if (integral < -maxIntegral) integral = -maxIntegral;

    derivative = (error - lastError) / 0.020;
    lastError = error;

    //Can uncomment for debugging purposes
    /*Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print(InertialSensor.rotation(degrees));*/

    double power = kP * error + kI * integral + kD * derivative;

    if (power > 100) power = 100;
    if (power < -100) power = -100;

    spinLeftDT(dir * power);
    spinRightDT(dir * power * -1);

    vex::task::sleep(20);
  }

  Controller.Screen.print("done");
  Controller.Screen.print(targetAngle);

  stopDT();
}