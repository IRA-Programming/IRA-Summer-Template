#include "arm.h"
#include "robot-config.h"
using namespace vex;


void liftArm(double deg, double speed) {
    Arm1.spinToPosition(deg, degrees, speed);
    Arm2.spinToPosition(deg, degrees, speed);
}

void clamp() {
    if (DoubleActingPiston.value() == 0) {
        DoubleActingPiston.set(true);
    }
    else if(DoubleActingPiston.value() == 1) {
        DoubleActingPiston.set(false);
    }
}