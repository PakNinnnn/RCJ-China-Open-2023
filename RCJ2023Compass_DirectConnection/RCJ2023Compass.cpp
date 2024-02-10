#include "RCJ2023Compass.h"

RCJ2023Compass::RCJ2023Compass(){

}

void RCJ2023Compass::begin(){
    pinMode(setZeroButton, INPUT);
    while (!Serial) delay(10);  // wait for serial port to open!
    
    if (!bno.begin())
    {
        Serial.print("No BNO055 detected");
        while (1);
    }

    calCompass();
}

bool RCJ2023Compass::pressedButton(){
    bool buttonState = !digitalRead(setZeroButton);

    if(buttonState == 1 && previousButtonState == 0)
        buttonPressed = true;
    else if (buttonState == 0 && previousButtonState == 1 && buttonPressed){
        buttonPressed = false;
    }

    previousButtonState = buttonState;
    
    return buttonPressed;
}

void RCJ2023Compass::setCompass()  {
  save = 0;
  delay(1);
  save = orientationData.orientation.x;
}

void RCJ2023Compass::calCompass(){
  bno.getCalibration(&sys, &gyro, &accel, &mag);
}

int RCJ2023Compass::getCaledCompass(){
    mynorth = orientationData.orientation.x - save;
    if(mynorth < 0)
        mynorth = mynorth + 360;
    return mynorth;
}

int RCJ2023Compass::getCompass(){
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

  if(pressedButton())
    RCJ2023Compass::setCompass();

  return RCJ2023Compass::getCaledCompass();
}