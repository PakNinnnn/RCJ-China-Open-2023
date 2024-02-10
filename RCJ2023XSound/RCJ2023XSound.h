#ifndef RCJ2023XSOUND_H
#define RCJ2023XSOUND_H

#define FRONT_PIN   A9   
#define BACK_PIN    A8   
#define LEFT_PIN    A7   
#define RIGHT_PIN   A6   

#define  MAX_RANG      (520)//the max measurement vaule of the module is 520cm(a little bit longer than  effective max range)
#define  ADC_SOLUTION  (1023.0)//ADC accuracy of Arduino UNO is 10bit

#include "Arduino.h"

class RCJ2023XSound{
    enum XSoundIndex {};
    public:
        RCJ2023XSound();
        void begin();
        int getXSound(int);
};

#endif
