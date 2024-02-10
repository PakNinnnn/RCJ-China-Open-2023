#include "RCJ2023M5Stack.h"

int16_t RCJ2023M5Stack::receivedValue = 0;
int16_t RCJ2023M5Stack::sendValue = 0;

String RCJ2023M5Stack::sendString = ""; 
String RCJ2023M5Stack::receivedString = ""; 

RCJ2023M5Stack::RCJ2023M5Stack(){

}

void RCJ2023M5Stack::begin(){
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveEvent_forString);
    Wire.onRequest(requestEvent_forString);
}

int16_t RCJ2023M5Stack::getReceivedValue(){
    return receivedValue;
}

void RCJ2023M5Stack::setSendValue(int16_t value){
    sendValue = value;
}

void RCJ2023M5Stack::receiveEvent(int numberOfByte){ 
  /*
  if (Wire.available() >= 2) { 
    byte b1 = Wire.read();
    byte b2 = Wire.read();
    
    RCJ2023M5Stack::receivedValue = (b2 << 8) | b1;
  }
  */
  return;
}

void RCJ2023M5Stack::receiveEvent_forString(int numberOfByte){ 
  if (numberOfByte > 2) {
    char* buffer = new char[numberOfByte + 1]; 
    int i = 0;
    while (i < numberOfByte) {
      buffer[i] = Wire.read();  
      i++;
    }
    buffer[numberOfByte] = '\0'; 
    receivedString = buffer;  
    delete[] buffer; 
    Serial.println(receivedString);
    RCJ2023M5Stack::receivedString = receivedString.substring(0, 1); 
  }
}


void RCJ2023M5Stack::requestEvent(){
  /*
  byte b1 = sendValue & 0xff; // Get the lower byte of the value
  byte b2 = (sendValue >> 8) & 0xff; // Get the upper byte of the value
  Wire.write(b1); // Send the lower byte
  Wire.write(b2); // Send the upper byte
  */
  return;
}

void RCJ2023M5Stack::requestEvent_forString(){
  // Convert the string to an array of integers representing its ASCII values
  const char* charString = sendString.c_str();
  int stringLength = strlen(charString);
  Wire.write((const uint8_t*)charString, stringLength);
}

 

void RCJ2023M5Stack::UI(int16_t compass, int16_t cam0, int16_t cam1, int16_t cam2, int16_t cam3, int16_t cam4, int16_t cam5){
  /*
  int myInt = compass;
  char myChar[6]; 
  dtostrf(myInt, 5, 0, myChar);    
  */
  String result = String(cam0) + "|" + String(cam1) + "|" + String(cam2) + "|" + String(cam3) + "|" + String(cam4) + "|" + String(cam5);
  Serial.println(receivedString);
  if(receivedString == "0")        sendString = "900";
  else if(receivedString == "1")   sendString = "111";
  else if(receivedString == "2")   sendString = result;
  else                             sendString = "400";
 
}

