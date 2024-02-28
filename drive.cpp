#include "subSystemHeaders/drive.hpp"

//helper functions
void setDrive(int left, int right){
    dlb = left;
    dlf = left;
    dlbt = left;
    drb = right;
    drf = right;
    drbt = right;
    dlb.set_brake_mode(MOTOR_BRAKE_COAST);
    dlf.set_brake_mode(MOTOR_BRAKE_COAST);
    dlbt.set_brake_mode(MOTOR_BRAKE_COAST);
    drb.set_brake_mode(MOTOR_BRAKE_COAST);
    drf.set_brake_mode(MOTOR_BRAKE_COAST);
    drbt.set_brake_mode(MOTOR_BRAKE_COAST);
}

//driver control functions
void setDriveMotors(){
    int power;
    int turn;
    int raw_power = controller.get_analog(ANALOG_LEFT_Y);
    int raw_turn = controller.get_analog(ANALOG_RIGHT_X);
   /* const double ramp_time = 1000;
    const double change = (20/ramp_time) * 127;
    double curr_joystick;
    static double ramp_joystick;
    curr_joystick = raw_power;
    if (std::abs(curr_joystick - ramp_joystick) >= change){
        if(curr_joystick > ramp_joystick){
        ramp_joystick += change;
        }
        else {
        ramp_joystick -= change;
        }
    }
    else{
        ramp_joystick = curr_joystick;
    }
    power = ramp_joystick;
    pros::delay(ramp_time * change);*/
    if (raw_power>=0){
        power = (raw_power * raw_power)/127;
    }
    else {
        power = (raw_power * raw_power)/-127;
    }

    if (raw_turn>=0){
        turn = (raw_turn * raw_turn)/127;
    }
    else {
        turn = (raw_turn * raw_turn)/-127;
    }
    int left = (power + turn) * 2;
    int right = (power - turn) * 2;
    setDrive(left, right);
}