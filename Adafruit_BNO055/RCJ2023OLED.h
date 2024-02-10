 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 display( 128 , 64 , &Wire2 , -1  ); 

void setup_OLED() {  
  if(!display.begin( SSD1306_SWITCHCAPVCC, 0x3C ) ) { 
    Serial.println( F( "SSD1306 allocation failed" ) );
    for(;;); 
  } 
}
 
void clearscreen(  ) { 
  display.clearDisplay();
  display.display(); 
} 

void displayint( int displayinteger , int textsize , int cursorX , int cursorY ) {
  display.setTextSize( textsize );            
  display.setTextColor( WHITE );         
  display.setCursor( cursorX , cursorY );
  display.println( displayinteger );
  display.display(); 
    display.clearDisplay();
  display.display(); 


}

void displaystring( String displaystring , int textsize1 , int cursorX1 , int cursorY1 ) {
  display.setTextSize( textsize1 );             
  display.setTextColor( WHITE );         
  display.setCursor( cursorX1 , cursorY1 );              
  display.println( displaystring );
  display.display(); 
  display.clearDisplay();
  display.display(); 

}

void drawrect( int fillornot , int X , int Y , int rectwidth , int rectlength , int linewidth ){
  switch( fillornot ){
    case 0 :{
      display.fillRoundRect( X , Y ,rectwidth , rectlength , linewidth , BLACK );
      display.display();
    }
    case 1 :{
      display.drawRoundRect( X , Y ,rectwidth , rectlength , linewidth , WHITE );
      display.display();
    }
  }
}
 
void drawcircle( int Xx , int Yy , int radius ){
  display.drawCircle( Xx , Yy , radius , WHITE );
  display.display();
} 
