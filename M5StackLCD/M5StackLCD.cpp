 #include "M5StackLCD.h"
    
M5StackLCD::M5StackLCD(int16_t brightness = 50, uint32_t backgroundColor = BLACK) : brightness(brightness), backgroundColor(backgroundColor){
    M5.Lcd.begin();
    M5.Lcd.fillScreen(backgroundColor);
    M5.Lcd.setBrightness(brightness);  
}

void M5StackLCD::drawRect(int16_t x, int16_t y, int16_t height, int16_t width, int16_t radius, uint32_t borderColor, bool fill = false, uint32_t fillColor = BLACK){
    int32_t computedX = (x - width / 2);
    int32_t computedY = (y - height / 2);

    computedX = computedX < 0 ? 0 : computedX;
    computedY = computedY < 0 ? 0 : computedY;

    if(fill)    M5.Lcd.fillRoundRect(computedX, computedY, height, width, radius, fillColor); 
    else        M5.Lcd.drawRoundRect(computedX, computedY, height, width, radius, borderColor); 
}

void M5StackLCD::drawCircle(int16_t x, int16_t y, int16_t radius, uint32_t borderColor, bool fill = false, uint32_t fillColor = BLACK){
    if(fill)    M5.Lcd.fillCircle(x, y, radius, fillColor);
    else        M5.Lcd.drawCircle(x, y, radius, borderColor);
}

void M5StackLCD::drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint32_t borderColor){
  M5.Lcd.fillTriangle(x1, y1, x2, y2, x3, y3, borderColor);
}
/*
void M5StackLCD::print(const char* string, int16_t x, int16_t y, int16_t fontSize, uint32_t fontColor, uint32_t bgColor){  
  M5.Lcd.setTextColor(fontColor,bgColor); 
  M5.Lcd.setTextSize(fontSize);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.printf(string);
}
*/

bool M5StackLCD::changeBgColor(uint32_t backgroundColor){
    this->backgroundColor = backgroundColor;
    M5.Lcd.fillScreen(backgroundColor);
    M5.update();

    return true;
}

bool M5StackLCD::changeBrightness(int16_t brightness){
    this->brightness = brightness; 
    M5.Lcd.setBrightness(brightness);  
    M5.update();

    return true;
} 

void M5StackLCD::clearScreen(){ 
  M5.Lcd.fillScreen(M5StackLCD::backgroundColor);
}

