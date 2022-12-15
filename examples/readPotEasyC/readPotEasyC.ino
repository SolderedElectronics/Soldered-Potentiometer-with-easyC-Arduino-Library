/**
 **************************************************
 *
 * @file        readPotEasyC.ino
 * @brief       Example template for easyC potentiometer
 *
 *
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "Potentiometer-easyC-SOLDERED.h"

PotentiometerEasyC pot;

void setup()
{
    Serial.begin(115200); // Start serial communication at 115200
    pot.begin();          // Start I2C communication on default address
    pot.setThreshold(10); // Set threshold value in percent to turn on the LED. Default is 50%
}

void loop()
{ 
    //Every 500 milliseconds print the potentiometer's value
    Serial.print("Potentiometer value is: ");
    Serial.println(pot.getValue());
    delay(500);
}
