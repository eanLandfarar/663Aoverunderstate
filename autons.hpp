#include "main.h"
#include "globals.hpp"
#include "shoot.hpp"
#ifndef AUTONS_HPP
#define AUTONS_HPP

//autonomous catapult control
void cataAut();

int num();

//autonomous intake control
void intakeAut(int power, int time);

//turning pid
void turnPid(double deg);

//auton select
int autonSelect();

//diff autons
void aut1();
void aut2();
void aut3();

#endif