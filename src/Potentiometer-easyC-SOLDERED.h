/**
 **************************************************
 *
 * @file        Potentiometer-easyC-SOLDERED.h
 * @brief       Header file for potentiometer with easyC.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#ifndef __POTENTIOMETER_EASYC__
#define __POTENTIOMETER_EASYC__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

class PotentiometerEasyC : public EasyC
{
  public:
    PotentiometerEasyC();
    int getValue();
    void setThreshold(byte threshold);

  protected:
    void initializeNative();

  private:
    int potValue;
    uint8_t threshold;
    int pin;
};

#endif
