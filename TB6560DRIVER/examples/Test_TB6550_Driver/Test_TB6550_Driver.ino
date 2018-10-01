#include "TB6560DRIVER.h"

#define  SWITCH3  false               // related to Switch3 on TB6560 Board
#define  SWITCH4  true                // related to Switch3 on TB6560 Board
#define  CLK_PIN  12                  // Clock-Pin T6560 Board connected to Arduino Pin
#define  DIR_PIN  11                  // Direction-Pin T6560 Board connected to Arduino Pin
#define  STEPS_PER_REVOLUTION  200    // Steppermotor specific
#define  STEPS_TO_GO 50               // Number of Steps to move

// Create an Instance of Driver and set up with parameters
TB6560DRIVER mystepper(CLK_PIN, DIR_PIN, SWITCH3, SWITCH4, STEPS_PER_REVOLUTION);

// Variable for Direction
bool richtung = true;

void setup() {
Serial.begin(250000);
// Set speed to xx RPM (Tested was 0.1 to 150 RPM with Excitation 2/8/16 )
mystepper.setSpeed (10);
}

void loop() {
// inverse direction every loop
richtung = !richtung;
mystepper.setDirection(richtung);

// send Serial actual speed
Serial.println(mystepper.go(STEPS_TO_GO));
// short breake
delay(500);
}




