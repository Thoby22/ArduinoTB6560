/*
 TB6560 - Library for controlling Stepper Motors from TB6560 3A CNC motor Driver.
 Based on Code by Omkar N. Tulaskar, November 26, 2017.
 Extended by Thomas Dose, Oktober 01, 2018
 Released into the public domain.
 */

#ifndef TB6560DRIVER_h
#define TB6560DRIVER_h

#include "Arduino.h"


class TB6560DRIVER{
	public:
	//constructors
	TB6560DRIVER(int  clock_pin,
                 int  direction_pin,
                 bool board_switch3,
                 bool board_switch4,
                 int  steps_per_revolution);
	
	int go(long number_of_steps);
	void setSpeed(long speed);
    void setDirection(bool motordirection);
	
	private :
    bool board_switch3;
    bool board_switch4;
	int clock_pin;
	int direction_pin;
	int number_of_steps; 
	int steps_per_revolution;
    int steps_per_sequence;
	long speed;
	unsigned long clock_delay;
	bool direction;
};

#endif
