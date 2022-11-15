/**
 **************************************************
 *
 * @file        Potentiometer-easyC-SOLDERED.cpp
 * @brief       Functions for potentiometer with easyC.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/


#include "Potentiometer-easyC-SOLDERED.h"

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void PotentiometerEasyC::initializeNative()
{
    pinMode(pin, INPUT);
}

/**
 * @brief                   Constructor for easyC potentiometer
 *
 *
 */
PotentiometerEasyC::PotentiometerEasyC()
{
    native = 0;
}

/**
 * @brief                   Function to get potentiometer value over I2C
 *
 * @return                  Potentiometer value
 */
int PotentiometerEasyC::getValue()
{
    byte data[2];
    Wire.requestFrom(0x30, 2);
    int i = 0;
    while (Wire.available() > 0)
    {
        data[i] = Wire.read();
        i++;
    }

    uint16_t resistance = 0;
    resistance = *(uint16_t *)data;

    return resistance;
}

/**
 * @brief                    Set threshold value to turn on LED on the breakout.
 *                           E.g. after 60% potentiometer's value, turn on the LED.
 *                           Default is 50%.
 *
 * @param _threshold         Integer value in percent which represent threshold.
 *
 * @return                   None
 */
void PotentiometerEasyC::setThreshold(byte _threshold)
{
    threshold = _threshold;
    // posalji mu threshold
    sendData(&threshold, 1);
}
