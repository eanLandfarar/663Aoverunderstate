#include "main.h"
#include "subSystemHeaders/autons.hpp"
#include "pros/motors.h"
#include "okapi/api/util/mathUtil.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "subSystemHeaders/shoot.hpp"
#include <atomic>
#include <string>
#include <cmath>
#include <memory>

//autonomous driving temporary (okapi)
std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
	.withMotors({10,9,8},{1,2,3})
// Green gearset, external ratio of (36.0 / 60.0), 4 inch wheel diameter, 11.5 inch wheel track
	.withDimensions({AbstractMotor::gearset::blue, (36.0 / 60.0)}, {{3.25_in, 10.5_in}, imev5GreenTPR})
	.build();


//autonomous catapult control
void cataAut(){
	vis.set_led_pwm(100);
while (true){
    if (vis.get_hue() > 100 && vis.get_hue() < 140){
        setCata(12000);
    } 
    else if ((vis.get_hue() < 101 && vis.get_hue() > 139) && (potentiometer.get_angle() > 45 && potentiometer.get_angle() < 49)){
        setCata(0);
    }
    else{
        setCata(12000);
    }
}
}

//autonomous intake control
void intakeAut(int power, int deg){
	intake.move_relative(deg, power);
}

//autonomous pneumatics control
void liftA(int value){
	if (value == 1){
		lift.set_value(true);
	}
	else {
		lift.set_value(false);
	}
}
void leftW(int value){
	if (value == 1){
		left_wing.set_value(true);
	}
	else {
		left_wing.set_value(false);
	}
}

void rightW(int value){
	if (value == 1){
		right_wing.set_value(true);
	}
	else {
		right_wing.set_value(false);
	}
}

void wings(int value){
	if (value == 1){
		left_wing.set_value(true);
		right_wing.set_value(true);
	}
	else {
		left_wing.set_value(false);
		right_wing.set_value(false);
	}
}

//turning pid
const double kpTurn = 0.4;
const double kiTurn = 0.0001;
const double kdTurn = 0.01;

void turnPid(double deg){
	imu.set_heading(0);
	dlb.set_brake_mode(pros::c::motor_get_brake_mode(MOTOR_BRAKE_HOLD));
	dlf.set_brake_mode(pros::c::motor_get_brake_mode(MOTOR_BRAKE_HOLD));
	dlbt.set_brake_mode(pros::c::motor_get_brake_mode(MOTOR_BRAKE_HOLD));
	drb.set_brake_mode(pros::c::motor_get_brake_mode(MOTOR_BRAKE_HOLD));
    drf.set_brake_mode(pros::c::motor_get_brake_mode(MOTOR_BRAKE_HOLD));
    drbt.set_brake_mode(pros::c::motor_get_brake_mode(MOTOR_BRAKE_HOLD));

	double target = deg;
	double totalError = 0;
	double prevError = 0;
	while (1){
		double error = std::fmod(target - imu.get_heading() + 180, 360) - 180;
		if (error < -180){
			error += 360;
		}
		totalError += error;
		double derivative = error - prevError;
		double power = kpTurn * error + kiTurn * totalError + kdTurn * derivative;
		dlb.move_velocity(power);
		dlf.move_velocity(power);
		dlbt.move_velocity(power);
		drb.move_velocity(-power);
        drf.move_velocity(-power);
        drbt.move_velocity(-power);

		if (std::abs(error) <= 2 && std::abs(derivative) <= 0.2){
			break;
		}
		prevError = error;
		pros::delay(5);
	}
	dlb.move_velocity(0);
	dlf.move_velocity(0);
	dlbt.move_velocity(0);
	drb.move_velocity(0);
    drf.move_velocity(0);
    drbt.move_velocity(0);
}



//diff autons
void aut1(){
	//step 1
	drive->moveDistance(33_in);
	turnPid(90);
	pros::delay(2);
	intakeAut(12000, -1000);
	pros::delay(200);
	//step 2
	drive->moveDistance(-8_in);
	turnPid(-90);
	pros::delay(2);
	drive->setMaxVelocity(70);
	intakeAut(12000, 3000);
	drive->moveDistance(6_in);
	//step 3
	turnPid(100);
	pros::delay(2);
	intakeAut(12000, -1200);
	pros::delay(400);
	//step 4
	turnPid(-170);
	pros::delay(2);
	intakeAut(12000, 3000);
	drive->moveDistance(8_in);
	turnPid(180);
	pros::delay(2);
	intakeAut(12000, -4000);
	drive->moveDistance(24_in);
	drive->moveDistance(-5_in);
	//step 7
	drive->setMaxVelocity(100);
	turnPid(100);
	pros::delay(2);
	drive->moveDistance(48_in);
}

void aut2(){
	rightW(1);
	turnPid(-90);
	pros::delay(2);
	rightW(0);
	pros::delay(2);
	turnPid(-165);
	pros::delay(2);
	intakeAut(12000, -4000);
	drive->moveDistance(30_in);
}

void aut3(){
	pros::Task matchload(cataAut);
	liftA(1); 
	drive->moveDistance(-3_in);
	pros::delay(5000);
	liftA(0);
	drive->moveDistance(44_in);
	leftW(1);
	turnPid(-45);
	pros::delay(2);
	drive->moveDistance(40_in);
	leftW(0);
	drive->moveDistance(-6_in);
	turnPid(-25);
	pros::delay(2);
	drive->moveDistance(34_in);
	turnPid(125);
	pros::delay(2);
	drive->moveDistance(50_in);
	turnPid(45);
	drive->moveDistance(24_in);
	
}
