#ifndef _ACTUATOR_H_
#define _ACTUATOR_H_

#include "robo_init.h"

void play(void);
void forward();
void back();
void right();
void left();
void stop();
void clockwise();
void forward_right();
void forward_left();
void back_right();
void back_left();

void anticlockwise();
void set_Omega(float get_Velocity);
void calculate_wheel_velocity();

#endif //!_ACTUATOR_H_
