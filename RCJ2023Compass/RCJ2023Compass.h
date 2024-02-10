
#ifndef RCJ2023COMPASS_H
#define RCJ2023COMPASS_H

#include <Arduino.h>

#define compassBaudRate 115200

class RCJ2023Compass{ 
    int16_t data[2];    
    public: 
        RCJ2023Compass();
        void begin();
        void getUartRead();
        int16_t uartRead();
        int16_t getCompass();
};

#endif