#ifndef RCJ2023LCD_H
#define RCJ2023LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <string.h>

#define SLAVE_ADDRESS 0x08

class RCJ2023LCD{
    static String sendString;
    static String receivedString;

    static void receiveEvent(int);
    static void requestEvent();

    public:
        RCJ2023LCD();
        void begin();
        static void setSendValue(String);
        static int16_t getReceivedValue();
        
        template <typename T>
        void print(T printingStuff, int16_t x, int16_t y, int16_t fontSize, uint32_t fontColor, uint32_t bgColor ){
            String sendPrintRequest = String(printingStuff);
     
            char str1[6]; char str2[6]; char str3[6]; 
            char str4[6]; char str5[6]; char str6[6]; 


            dtostrf(printingStuff, 5, 0, str1);
            dtostrf(x, 5, 0, str2);
            dtostrf(y, 5, 0, str3);
            dtostrf(fontSize, 5, 0, str4);
            dtostrf(fontColor, 5, 0, str5);
            dtostrf(bgColor, 5, 0, str6); 

            char combinedString[40]; 
            snprintf(combinedString, sizeof(combinedString), "%s|%s|%s|%s|%s|%s", str1, str2, str3, str4, str5, str6);
            
            const char* sendString = combinedString;

            setSendValue(sendString);
        }

        void changeScreenColor(int color){
            char colorStr[6];

            dtostrf(color, 5, 0, colorStr);

            const char* sendString = colorStr;
            setSendValue(sendString);
        }
        
};

#endif
