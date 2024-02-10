#ifndef RCJ2023Grayscale_H
#define RCJ2023Grayscale_H

#include <Arduino.h>  

#define BACK_GS1  A2
#define BACK_GS2  A1
#define BACK_GS3  A0

#define FRONT_GS1 A3
#define FRONT_GS2 A4
#define FRONT_GS3 A5

#define RIGHT_GS1 A15
#define RIGHT_GS2 A16
#define RIGHT_GS3 A17

#define LEFT_GS1  A20
#define LEFT_GS2  A21
#define LEFT_GS3  A22

class RCJ2023Grayscale{
    const int16_t threshold = 1023;

    public:
        RCJ2023Grayscale();
        void begin();
        bool checkWhiteline(int);
        int getGrayscale(int, int);

};
#endif 