/**
 **************************************************
 *
 * @file        Read_Potentiometer_EasyC.ino
 * @brief       Example for reading a value from the potentiometer and setting a threshold to LED on the breakout.
 *
 *  Connect the breakout to the Dasduino or Inkplate via easyC and upload this code.
 *  Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/
 *  Don't have an Inkplate? Get it here: https://soldered.com/categories/inkplate/
 *  Don't have easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/
 *
 *  This example will show you how to read the value from the potentiometer and set the threshold value
 *  after which the LED will be turned on. The default threshold for the LED is 50% or 512 if you look
 *  at the raw analog read value (0 - 1023). This value can be adjusted by calling the setThreshold()
 *  function and entering a number from 0 to 100 representing the threshold percentage or with the function
 *  setRawThreshold() where you enter the raw value (0 - 1023).
 *
 * @link        https://www.solde.red/333193
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

// Include Soldered library for the potentiometer with easyC
#include "Potentiometer-easyC-SOLDERED.h"

// Create an object for potentiometer with easyC
PotentiometerEasyC pot;

void setup()
{
    // Start serial communication at 115200 baud rate
    Serial.begin(115200);

    // Start I2C communication on default address (0x30)
    pot.begin();

    // If you want another I2C address, enter it in the bracket
    // You can set another I2C address (0x31 - 0x37) by changing address switches on the breakout
    // pot.begin(0x31);

    // Set threshold value in percent to turn on the LED. Default is 50%
    pot.setThreshold(20.5);

    // Or you can set the raw threshold value (0 - 1023)
    // pot.setRawThreshold(128);
}

void loop()
{
    // Print a potentiometer values every 200 milliseconds

    Serial.print("Potentiometer value is: ");
    Serial.print(pot.getValue()); // Get the potentiometer percentage value
    Serial.print("% or raw: ");
    Serial.println(pot.getRawValue()); // Get the potentiometer raw value

    // Wait 200 milliseconds
    delay(200);
}
