#include "functions.h"
#include "robot-config.h"
#include "vex.h"

using namespace vex;

const double GEAR_RATIO = 5.0 / 3; //remember to make the first number a decimal, otherwise the quotient will be rounded down
const double WHEEL_DIAMETER = 3.25;

double inchesToDegrees(double inches) {
    return ((inches / (M_PI * WHEEL_DIAMETER)) * 360 * GEAR_RATIO);
}

double degreesToInches(double deg) {
    return ((deg / (360 * GEAR_RATIO)) * (M_PI * WHEEL_DIAMETER));
}


void setDTPosition(double inches) {

    double deg = inchesToDegrees(inches);

    leftDrive.setPosition(deg, degrees);
    rightDrive.setPosition(deg, degrees);
}

void stopDT() {
    leftDrive.stop(brake);
    rightDrive.stop(brake);
}


void spinRightDT(double velocity) {
    rightDrive.spin(forward, velocity, percent);
}

void spinLeftDT(double velocity) {
    leftDrive.spin(forward, velocity, percent);
}

void spinDT(double velocity) {
    spinRightDT(velocity);
    spinLeftDT(velocity);
}

void spinDTPosition(double rpmVelocity, double targetInches){

    setDTPosition(0);
    double targetDegrees = inchesToDegrees(targetInches);

    leftDrive.spinToPosition(targetDegrees, degrees, rpmVelocity, rpm, false);
    rightDrive.spinToPosition(targetDegrees, degrees, rpmVelocity, rpm, true);
}

void turnForTime(double velocity, double time) {
    spinRightDT(-velocity);
    spinLeftDT(velocity);
    wait(time, msec);
    stopDT();
} 

void runIntake(){
    intakeMotor.spin(forward, 100, percent);
}

void runOutake(){
    intakeMotor.spin(reverse, 100, percent);
}

void stopIntake(){
    intakeMotor.stop(coast);
}

//Copy This Funtion When Teaching
void spinDTWithDistance(double inches, double velocity) {
    setDTPosition(0);
    spinDT(velocity);
    while (LF.position(degrees) < inchesToDegrees(inches)) {
        vex::task::sleep(20);
    }
    stopDT();
}

void turnDTWithAngle(double angle, double velocity) {
    InertialSensor.setHeading(0, degrees);
    RF.spin(forward, velocity, percent);
    RM.spin(forward, velocity, percent);
    RB.spin(forward, velocity, percent);
    LF.spin(reverse, velocity, percent);
    LM.spin(reverse, velocity, percent);
    LB.spin(reverse, velocity, percent);
    while (fabs(InertialSensor.heading(degrees)) < fabs(angle)) {
        vex::task::sleep(20);
    }
    stopDT();
}
























/*spinRightDT(-velocity);
    spinLeftDT(velocity);
    wait(time, msec);
    stopDT();*/
