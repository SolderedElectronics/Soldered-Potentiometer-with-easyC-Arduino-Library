/**
 **************************************************
 *
 * @file        attiny_firmware.ino
 * @brief       Attiny firmware for potentiometer with easyC.
 *
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>


int addr = DEFAULT_ADDRESS; // 0x30
uint16_t analogValue;       // For reading potentiometer analog value
uint16_t threshold = 512;   // Raw default threshold value (50%)

#define POT_PIN           PA5 // Potentiometer pin on the attiny
#define LED_THRESHOLD_PIN PA4 // LED pin for indicating the threshold

void setup()
{
    // Set I2C address selector as input and get I2C address
    initDefault();
    addr = getI2CAddress();

    // Init I2C communication
    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    pinMode(POT_PIN, INPUT);
    pinMode(LED_THRESHOLD_PIN, OUTPUT);
}

void loop()
{
    // Read potentiometer analog value
    analogValue = analogRead(POT_PIN);

    // Set a threshold LED on the breakout depending on the set threshold
    if (analogValue > threshold)
    {
        digitalWrite(LED_THRESHOLD_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_THRESHOLD_PIN, LOW);
    }
}

// When the breakout receives the data over I2C, this function is executing
void receiveEvent(int howMany)
{
    // Array for the raw threshold in bytes
    uint8_t rawThresholdBytes[2];

    // If data is incoming
    if (Wire.available())
    {
        // Read 2 bytes which represents the raw threshold value
        Wire.readBytes(rawThresholdBytes, 2);
    }

    // Converts this value into uint16_t
    threshold = *(uint16_t *)rawThresholdBytes;
}

// When the master requests the data, this function is executing
void requestEvent()
{
    // Because I2C sends bytes, separate this value into 2 appropriate bytes for sending
    uint8_t *analogValueForSend = (uint8_t *)&analogValue;
    Wire.write(analogValueForSend, 2);
}
