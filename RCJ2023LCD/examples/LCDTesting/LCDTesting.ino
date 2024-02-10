#include <RCJ2023LCD.h>

RCJ2023LCD LCD;

void setup() {
  // put your setup code here, to run once:
  LCD.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  //Either do LCD.print() or LCD.changeScreenColor();
  LCD.print(analogRead(A0), 10, 10, 3, 1, 1);   
  //LCD.changeScreenColor(3);
}
