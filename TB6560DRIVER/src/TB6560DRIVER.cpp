/*
  TB6560 - Library for controlling Stepper Motors from TB6560 3A CNC motor Driver.
  Based on Code by Omkar N. Tulaskar, November 26, 2017.
  Extended by Thomas Dose, Oktober 01, 2018
  Released into the public domain.
*/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "TB6560DRIVER.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//						Setting up the Arduino pins from the User

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TB6560DRIVER::TB6560DRIVER(int clock_pin,
                           int direction_pin,
                           bool board_switch3,
                           bool board_switch4,
                           int steps_per_revolution)
{
	this->clock_pin=clock_pin;
	this->direction_pin=direction_pin;
    this->steps_per_revolution = steps_per_revolution;
    
    // Setting Switches on TB6560 Board
    if ( !board_switch3 && !board_switch4){this->steps_per_sequence = 1;}
    if (  board_switch3 && !board_switch4){this->steps_per_sequence = 2;}
    if (  board_switch3 && board_switch4) {this->steps_per_sequence = 8;}
    if ( !board_switch3 && board_switch4) {this->steps_per_sequence = 16;}
	
	//Setting Arduino pins connected to clock and direction as output
	pinMode(this->direction_pin,OUTPUT);
	pinMode(this->clock_pin,OUTPUT);
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//											Functions for setting up the speed

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void TB6560DRIVER::setDirection(bool motordirection)
{
	this-> direction=motordirection;
	
	if(this-> direction)
	{
		digitalWrite(this->direction_pin,HIGH);
	}
	else
	{
		digitalWrite(this->direction_pin,LOW);
	}
}

//		** This will set the speed in revolutions per minute **

void TB6560DRIVER::setSpeed(long speed)
{
    this->speed=speed;
    
    if (speed > 300) this->speed= 300;
    this->clock_delay = ((60L * 1000L * 1000L )/ this->steps_per_revolution / this->speed / steps_per_sequence - 8 ) / 2;
    this->clock_delay =this->clock_delay;
}

//      ** This drives the Motor and returns the actual Speed in RPM **
int TB6560DRIVER::go(long number_of_steps)
{
    long now= micros();
    int counter = 0;
    while (counter < number_of_steps){
        for (int steps = 0; steps < steps_per_sequence; steps++){
            // Pulse ausgeben
            digitalWrite(this->clock_pin, HIGH);
            delayMicroseconds(this->clock_delay);
            digitalWrite(this->clock_pin, LOW);
            delayMicroseconds(this->clock_delay);
        }
        counter++;
    }
    return ((60000000 / (micros() - now) *  (number_of_steps) / double(steps_per_revolution)));
}



