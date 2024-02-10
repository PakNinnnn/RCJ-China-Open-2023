#include "RCJ2023Compass.h"

RCJ2023Compass::RCJ2023Compass(){

}

void RCJ2023Compass::begin(){
  Serial4.begin(compassBaudRate);
}

int16_t RCJ2023Compass::uartRead(){
  while(not(Serial4.available()));  
  return Serial4.read();
}

void RCJ2023Compass::getUartRead(){
  while (Serial4.available() != 0) {  
    Serial4.read();
  } 
  for(int i = 0; i < 2; i++ ) {
    data[i] = uartRead();
  } 
}

int16_t RCJ2023Compass::getCompass(){
  getUartRead();

  int16_t reading = (data[0] & 0b0000000000111111) + ((data[1] & 0b0000000000111111) << 6);

  return reading > 359 ? 359 : reading;
}


/*
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

double save, mynorth, north;
uint16_t BNO055_SAMPLERATE_DELAY_MS = 10; //how often to read data from the board
uint16_t PRINT_DELAY_MS = 30; // how often to print the data
sensors_event_t orientationData;
uint8_t sys, gyro, accel, mag = 0;
int x= 2;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup(){ 
  Serial.begin(115200);
  pinMode(x,INPUT); 
  pinMode(13, OUTPUT);
  while (!Serial) delay(10);  // wait for serial port to open!
  
  if (!bno.begin())
  {
    Serial.print("No BNO055 detected");
    while (1){ 
      digitalWrite(13, HIGH);
    }
  }
  cal_Compass();
}

int previousButtonState = 0; 
bool buttonPressed = false;
bool pressedButton(){
  bool buttonState = digitalRead(x);

  if(buttonState == 1 && previousButtonState == 0)
    buttonPressed = true;
  else if (buttonState == 0 && previousButtonState == 1 && buttonPressed){
    buttonPressed = false;
  }

  previousButtonState = buttonState;
  
  return buttonPressed;
}

void sendOpenMVData(int a) {
  Serial.write(a & 0b00000000000111111); // Send the lower 8 bits
  Serial.write((a & 0b0000111111000000 ) >> 6); // Send the upper 8 bits
}


void loop(){
  digitalWrite(13, LOW);
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  //Serial.println(get_Compass());
  if(pressedButton())
    set_Compass();
  int compassReading = get_Compass();
  sendOpenMVData(compassReading);
  //Serial.println(digitalRead(x));


}

int get_Compass(){// Orientation
  mynorth = orientationData.orientation.x - save;
  if(mynorth < 0)
    mynorth = mynorth + 360;
  return mynorth;
}

void set_Compass()  {
  save = 0;
  delay(1);
  save = orientationData.orientation.x;
}

void cal_Compass(){
  bno.getCalibration(&sys, &gyro, &accel, &mag);
}
*/