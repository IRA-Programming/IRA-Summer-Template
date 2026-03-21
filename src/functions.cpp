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
    bottomIntakeMotor.spin(forward, 100, percent);
    middleIntakeMotor.spin(reverse, 100, percent);
    topIntakeMotor.spin(forward, 100, percent);
}

void runOutake(){
    bottomIntakeMotor.spin(reverse, 100, percent);
    middleIntakeMotor.spin(forward, 100, percent);
    topIntakeMotor.spin(reverse, 100, percent);
}

void stopIntake(){
    bottomIntakeMotor.stop(coast);
    middleIntakeMotor.stop(coast);
    topIntakeMotor.stop(coast);
}
























/*spinRightDT(-velocity);
    spinLeftDT(velocity);
    wait(time, msec);
    stopDT();*/
