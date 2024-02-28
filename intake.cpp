#include "subSystemHeaders/intake.hpp"

void setIntake(int power){
    intake = -power;
}

void setIntakeMotors(){
    int intakePower = 1000 * ((controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) - (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)));
    setIntake(intakePower);
}