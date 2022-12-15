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


int addr = DEFAULT_ADDRESS;
uint16_t resistance;
byte threshold = 50;

void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    pinMode(PA5, INPUT);  // Potentiometer pin on the attiny
    pinMode(PA4, OUTPUT); // LED pin
}

void loop()
{
    resistance = analogRead(PA5);
    if(resistance > (threshold * 0.01 * 1024))
    {
      digitalWrite(PA4, HIGH);
    }
    else
    {
      digitalWrite(PA4, LOW);
    }

    delay(50); //Read resistance every 50 milliseconds

}


void receiveEvent(int howMany) 
{
    while (Wire.available())
    {
        threshold = Wire.read();
    }
}

void requestEvent() 
{
    uint8_t *resistanceToSend = (uint8_t*)&resistance;
    Wire.write(resistanceToSend, 2);
}
