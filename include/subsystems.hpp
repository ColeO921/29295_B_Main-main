//subsystems.hpp
#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

//make sure to extern your motors here
extern pros::Motor preroller;
extern pros::Motor intake;
extern pros::Motor tall_scorer;
extern pros::Motor middle_scorer;
extern ez::Piston matchLoader;
extern ez::Piston intakePiston;
extern pros::Motor scoreMoter;