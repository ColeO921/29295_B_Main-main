//subsystems.cpp
#include "subsystems.hpp"
#include "api.h"

ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-13, 12, 11},    // Left Chassis Ports (negative port will reverse it!)
    {16, -15, -14},  // Right Chassis Ports (negative port will reverse it!)

    17,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    360);   // Wheel RPM = cartridge * (motor gear / wheel gear)

// Motors
pros::Motor intake(18);
pros::Motor scoreMoter(6);
pros::Motor preroller(-20); //negitive motor (reversed)

// Pneumatics
inline ez::Piston intakePiston ('C');
inline ez::Piston matchLoader ('E');