#include <RCJ2023OpenMV.h>

RCJ2023OpenMV cam;

void setup() {
  // put your setup code here, to run once:
  cam.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(cam.getOpenMV(0));
}
