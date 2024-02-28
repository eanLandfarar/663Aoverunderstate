#include "main.h"
#include "pros/adi.hpp"
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

//drive base motors
extern pros::Motor dlb;
extern pros::Motor dlf;
extern pros::Motor dlbt;
extern pros::Motor drb;
extern pros::Motor drf;
extern pros::Motor drbt;

//cata motors
extern pros::Motor cata11;
extern pros::Motor cata5;

//intake motors
extern pros::Motor intake;

//pneumatics
extern pros::ADIDigitalOut left_wing;
extern pros::ADIDigitalOut right_wing;
extern pros::ADIDigitalOut lift;
extern pros::ADIDigitalOut elevate;

//sensors
extern pros::IMU imu;
extern pros::Optical vis;
extern pros::ADIDigitalIn selector;
extern pros::ADIPotentiometer potentiometer;

//controller
extern pros::Controller controller;

//miscellaneous
#endif