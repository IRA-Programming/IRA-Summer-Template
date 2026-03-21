/* Helps prevent header files from being included multiple times*/
#pragma once

/* These prevent header files from being included multiple times*/


void drivePID(double targetInches, double kP = 6, double kI = 0.15, double kD = 0.05);
void turnPID(double targetAngle, double kP = 0.5, double kI = 0.005, double kD = 0.04);


