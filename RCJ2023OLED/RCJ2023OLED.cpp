
#include "RCJ2023OLED.h"

RCJ2023OLED::RCJ2023OLED(){
  
}

void RCJ2023OLED::begin(){
  if(!oled.begin(SSD1306_SWITCHAPVCC, 0x3C))
    Serial.println(F("OLED FAILED"))
  oled.setTextColor(WHITE);
}

void RCJ2023OLED::displayInt(int CurX, int CurY, int data, int textsize){
  oled.setTextsize(textsize);
  oled.setCursor(CurX, CurY);
  oled.println( data );
  oled.display();
  oled.clearScreen();
  oled.display();
}

void RCJ2023OLED::displayString(int CurX, int CurY, String com, int size){
  oled.setTextsize(size);
  oled.setCursor(CurX, CurY);
  oled.println( com );
  oled.display();
  oled.clearScreen();
  oled.display();
}

void RCJ2023OLED::drawRect(int CurX, int CurY, int recW, int recL, int linewidth ){
  oled.fillRoundRect(CurX, CurY, recW, recL, linewidth, WHITE )
}

void RCJ2023OLED::drawCir(int X, int Y, int radius){
  oled.drawCircle(X, Y, radius, WHITE);
  oled.display();
}

void RCJ2023OLED::clear(){
  oled.clearDisplay();
  oled.display();
}