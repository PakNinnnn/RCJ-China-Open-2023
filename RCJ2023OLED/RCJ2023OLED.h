#ifndef RCJ2023OLED_H
#define RCJ2023OLED_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
 


class RCJ2023OLED{
    int SCREEN_WIDTH {128};
    int SCREEN_HEIGHT {32};
    int OLED_RESET {-1};

    public:

        Adafruit_SSD1306 display(128, 32, &Wire, -1);

        RCJ2023OLED();
        void begin();
        void displayInt(int, int, int, int);
        void displayString(int, int, String, int);
        void drawRect(int, int, int, int, int);
        void drawCir(int, int, int);
        void clear();
};

#endif