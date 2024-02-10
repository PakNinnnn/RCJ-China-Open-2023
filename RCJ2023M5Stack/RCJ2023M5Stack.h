#ifndef RCJ2023M5STACK_H
#define RCJ2023M5STACK_H

#include <Arduino.h> 
#include <Wire.h>
#include <String>

#define SLAVE_ADDRESS 0x08

class RCJ2023M5Stack{
    static int16_t sendValue;
    static int16_t receivedValue;

    static String sendString;
    static String receivedString;
 
    static void requestEvent();
    static void requestEvent_forString();
    static void receiveEvent(int); 
    static void receiveEvent_forString(int);

    public:
        RCJ2023M5Stack();
        void begin();
        static void setSendValue(int16_t);
        static int16_t getReceivedValue();

        void UI(int16_t, int16_t, int16_t, int16_t, int16_t, int16_t, int16_t); 
};

#endif