# ifndef RCJ2023DRIBBLER_H
# define RCJ2023DRIBBLER_H

#include <Arduino.h>
#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MOTOR_PIN 2

class RCJ2023Dribbler{
    int DELAY {1000};

    Servo motor;

    long int initialTime = millis();

    public:
        RCJ2023Dribbler();
        void begin();
        void spin(bool, int);
};

#endif