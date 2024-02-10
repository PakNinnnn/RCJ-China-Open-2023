#include <RCJ2023Dribbler.h>

RCJ2023Dribbler dribbler;

void setup() {
  // put your setup code here, to run once:
  //dribbler.begin(); 
  Serial.begin(9600);
  pinMode(12, INPUT); 
}

   
void loop() {
  // put your main code here, to run repeatedly:  
  
  if(digitalRead(12) == 0)
    dribbler.spin(true, 12);
  else
    dribbler.spin(false, 0);

  Serial.println(digitalRead(12));

  
}
