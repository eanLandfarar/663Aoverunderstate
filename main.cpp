#include "main.h"
#include "SubSystemHeaders/globals.hpp"
#include "SubSystemHeaders/shoot.hpp"
#include "SubSystemHeaders/drive.hpp"
#include "SubSystemHeaders/intake.hpp"
#include "subSystemHeaders/autons.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include <atomic>
#include <string>
#include <cmath>
#include <memory>

std::shared_ptr <ChassisController> chassis = ChassisControllerBuilder()
	.withMotors({18,20},{17,19})
// Green gearset, external ratio of (36.0 / 60.0), 4 inch wheel diameter, 11.5 inch wheel track
	.withDimensions({AbstractMotor::gearset::blue, (36.0 / 60.0)}, {{3.25_in, 10.5_in}, imev5GreenTPR})
	.build();

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void intakeAut(int power, int deg);

//auton selector
int selectVal = 1;
int autonSelect(){
	if (selector.get_new_press()){
		selectVal = selectVal + 1;
	}
	if (selectVal > 3){
		selectVal = 1;
	}
	if (selectVal == 1){
		vis.set_led_pwm(0);
	} else if (selectVal == 2){
		vis.set_led_pwm(25);
	} else if (selectVal == 3){
		vis.set_led_pwm(100);
	}
	return selectVal;
}

//this would be where auton selector would be
void competition_initialize() {
	pros::lcd::initialize();
	while (true){
		autonSelect();
		std::string str = std::to_string(selectVal);
		pros::lcd::set_text(1, str);
	}
}

//autonomous period
void autonomous() {
	if (selectVal == 1){
		aut1();
	} else if (selectVal == 2){
		aut2();
	} else if (selectVal == 3){
		aut3();
	}
}

//driver control period
void opcontrol() {

	while (true) {

		std::string valu = std::to_string(potentiometer.get_angle());
		pros::lcd::set_text(1, valu);
		//drive function
		setDriveMotors();

		//catapult function
		setCataMotors();

		setIntakeMotors();

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
			lift.set_value(true);
		}
		else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
			lift.set_value(false);
		}
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
			elevate.set_value(true);
			lift.set_value(false);
		}
		else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
			elevate.set_value(false);
		}
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			left_wing.set_value(true);
		}
		else {
			left_wing.set_value(false);
		}
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			right_wing.set_value(true);
		}
		else {
			right_wing.set_value(false);
		}
	

		pros::delay(20);
	}
}
