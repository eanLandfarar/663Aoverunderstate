#include "main.h"
#include "subSystemHeaders/globals.hpp"

//drive base motors
pros::Motor dlb(9, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor dlf(8, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor dlbt(10, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor drb(2, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor drf(3, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor drbt(1, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);

//cata motors
pros::Motor cata11(5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor cata5(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//intake motors
pros::Motor intake(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

//pneumatics
pros::ADIDigitalOut left_wing('D');
pros::ADIDigitalOut right_wing('C');
pros::ADIDigitalOut lift('A');
pros::ADIDigitalOut elevate('B');

//sensors
pros::IMU imu(7);
pros::Optical vis(20);
pros::ADIDigitalIn selector('E');
pros::ADIPotentiometer potentiometer('F');

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);