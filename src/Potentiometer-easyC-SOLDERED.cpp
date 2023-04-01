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
 * @brief                   Function to get raw potentiometer value over I2C
 *
 * @return                  Raw potentiometer value (0 - 1023)
 */
int PotentiometerEasyC::getRawValue()
{
    // Read bytes of raw potentiometer data
    char data[2];
    readData(data, 2);

    // Convert it to uint16_t
    uint16_t resistance = 0;
    resistance = *(uint16_t *)data;

    // Return converted value
    return resistance;
}

/**
 * @brief                   Function to get percentage potentiometer value over I2C
 *
 * @return                  Percentage potentiometer value (0 - 100)
 */
float PotentiometerEasyC::getValue()
{
    return (getRawValue() / float(1023)) * 100;
}

/**
 * @brief                    Set the raw threshold value to turn on LED on the breakout.
 *                           E.g. after 512 potentiometer's value, turn on the LED.
 *
 * @param uint16_t threshold         Integer value which represents raw threshold value. (0 - 1023)
 *
 * @return                   None
 */
void PotentiometerEasyC::setRawThreshold(uint16_t threshold)
{
    // Check if the threshold is the proper value
    if (threshold < 0 || threshold > 1023)
    {
        return;
    }

    // Convert raw threshold value into 2 bytes for sending
    uint8_t *rawThreshold = (uint8_t *)&threshold;

    // Send raw threshold
    sendData(rawThreshold, 2);
}

/**
 * @brief                    Set the  threshold value in percentage to turn on LED on the breakout.
 *                           E.g. after 50% potentiometer's value, turn on the LED.
 *
 * @param float threshold    Value which represents percentage threshold value. (0 - 100)
 *
 * @return                   None
 */
void PotentiometerEasyC::setThreshold(float threshold)
{
    // Check if the threshold is the proper value
    if (threshold < 0 || threshold > 100)
    {
        return;
    }

    // Convert percentage threshold to raw value and send it
    uint16_t rawThreshold = threshold * 0.01 * 1024;
    setRawThreshold(rawThreshold);
}
