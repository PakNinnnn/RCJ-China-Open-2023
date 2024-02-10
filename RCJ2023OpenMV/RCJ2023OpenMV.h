#ifndef RCJ2023OPENMV_H
#define RCJ2023OPENMV_H

#define baudRate 500000

/*
    OpenMV  |   Teensy
      P4         9
      P5         10
*/

#include <Arduino.h>  

class RCJ2023OpenMV{ 
    int16_t data[2];    
    public: 
        void begin();
        void getUartRead();
        int16_t uartRead();
        int16_t getOpenMV(int16_t);
};

#endif
