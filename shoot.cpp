#include "subSystemHeaders/shoot.hpp"

//helper functions
void setCata(int power){
    cata11 = -power;
    cata5 = -power;
}

//driver control functions
void setCataMotors(){
    vis.set_led_pwm(100);
    if (vis.get_hue() > 100 && vis.get_hue() < 140){
        setCata(12000);
    } 
    if ((vis.get_hue() < 101 && vis.get_hue() > 139) && (potentiometer.get_angle() > 200 && potentiometer.get_angle() < 250)){
        setCata(0);
    }
    else{
        setCata(12000);
    }
}