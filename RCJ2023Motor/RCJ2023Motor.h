#ifndef RCJ2023MOTOR_H
#define RCJ2023MOTOR_H

#define MTR1_DIR 24
#define MTR1_PWM 5
#define MTR2_DIR 25
#define MTR2_PWM 6
#define MTR3_DIR 26
#define MTR3_PWM 7
#define MTR4_DIR 27
#define MTR4_PWM 8

#define compensateSpd 30
#define tolerant    7

#include <Arduino.h>

class RCJ2023Motor{
    
    public:
        int dir1, dir2, dir3, dir4;
        RCJ2023Motor();
        void begin(int, int, int, int);
        void move(int, int, int, int);
        void moveAtAngle(int, int, int, int);
        void stop();
};

 #endif