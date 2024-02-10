#ifndef M5STACKLCD_H
#define M5STACKLCD_H

#include <M5Stack.h>    
#include <Arduino.h>

class M5StackLCD{

    public:
        int16_t brightness;
        uint32_t backgroundColor;
        M5StackLCD(int16_t, uint32_t);
        void drawRect(int16_t, int16_t, int16_t, int16_t, int16_t, uint32_t, bool, uint32_t);
        void drawCircle(int16_t, int16_t, int16_t, uint32_t, bool, uint32_t);
        void drawTriangle(int16_t, int16_t, int16_t, int16_t, int16_t, int16_t, uint32_t);
        //void print(const char*, int16_t, int16_t, int16_t, uint32_t, uint32_t); 
        bool changeBgColor(uint32_t);
        bool changeBrightness(int16_t);
        void clearScreen();

        template <typename T>
        void print(T printingStuff, int x, int y, int fontSize, int fontColor, int bgColor){
            M5.Lcd.setTextColor(fontColor,bgColor); 
            M5.Lcd.setTextSize(fontSize);
            M5.Lcd.setCursor(x, y);

            if(std::is_same<T, int>::value || std::is_same<T, float>::value){
                String numberStr = String(printingStuff);
                const char* charStr = numberStr.c_str();  
                M5.Lcd.printf(charStr);
            }
            else{
                String stringData = String(printingStuff);
                const char* charData = stringData.c_str();
                M5.Lcd.printf(charData);
            }
        }
};

#endif // M5STACKLCD_H