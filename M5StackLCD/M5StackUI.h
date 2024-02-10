#ifndef M5STACKUI_H
#define M5STACKUI_H

#include <M5Stack.h>
#include <Arduino.h>
#include <Math.h> 
#include <string>
//include <string.h>
#include "M5StackLCD.h"

#define sqrXSep_normal 76
#define sqrXSep_middle 77
#define sqrYSep_normal 98

#define initialBoxX 16
#define initialBoxY 38
#define endingBoxX 245
#define endingBoxY 136

#define SLAVE_ADDRESS 0x08
/*
      Teensy | M5Stack
SDA     18       22
SDL     19       21
*/

class M5StackUI : public M5StackLCD{
    int16_t currentPage, currentX, currentY;
    bool resetBGColor = false;
    bool menuPage = false;
    bool compassPage = false;
    bool camPage = false;
    bool distSenPage = false;
    bool grayScalePage = false;
    bool kickDribPage = false;
    bool mtrPage = false;
    bool commPage = false;
    bool debugPage = false;

    int compassArrowInitialX = 99;
    int compassArrowInitialY = 68;
    int compassArrowInitialAngle = 0;

    int cameraBallInitialX = 90;
    int cameraBallInitialY = 55;
    int cameraBallInitialAngle = 0;

    void pushI2CReveive(int16_t);
    int16_t pullI2CRequest(int16_t);

    void pushI2CReveive_forString(const char*);
    String pullI2CRequest_forString(int16_t);

    public:
        M5StackUI(int16_t, uint32_t); 
        void UI();
        void menu();
        void newArrow(int&, int&, int);
        void newball(int& , int&, int);
        void compassUI();
        void camUI();
        void distSenUI();
        void grayScaleUI();
        void kickDribUI();
        void mtrUI();
        void commUI();
        void debugUI(); 
};

#endif 
