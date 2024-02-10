
#ifndef RCJ2023COMPASS_H
#define RCJ2023COMPASS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define setZeroButton 11

class RCJ2023Compass{ 
    double save, mynorth, north;
    uint16_t BNO055_SAMPLERATE_DELAY_MS = 10; //how often to read data from the board
    uint16_t PRINT_DELAY_MS = 30; // how often to print the data
    sensors_event_t orientationData;
    uint8_t sys, gyro, accel, mag = 0;
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

    int previousButtonState = 0; 
    bool buttonPressed = false;

    public:
        RCJ2023Compass();
        void begin();
        bool pressedButton();
        void setCompass();
        void calCompass();
        int getCaledCompass();
        int getCompass();
};

#endif