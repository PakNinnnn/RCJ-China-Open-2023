#include "RCJ2023LCD.h"

String RCJ2023LCD::sendString = "";
String RCJ2023LCD::receivedString = "";

RCJ2023LCD::RCJ2023LCD(){

}

void RCJ2023LCD::begin(){
    Wire2.begin(SLAVE_ADDRESS); 
    Wire2.onReceive(receiveEvent); 
    Wire2.onRequest(requestEvent);
}

void RCJ2023LCD::setSendValue(String stringToSend){
    RCJ2023LCD::sendString = stringToSend;
}

void RCJ2023LCD::receiveEvent(int numBytes){
    if (numBytes > 2) {
        char* buffer = new char[numBytes + 1]; 
        int i = 0;
        while (i < numBytes) {
            buffer[i] = Wire2.read();  
            i++;
        }
        buffer[numBytes] = '\0';  
        receivedString = buffer; 
        delete[] buffer;    

        //Serial.println((receivedString.substring(0, 0)));
    }
}

void RCJ2023LCD::requestEvent(){
    /*
    int myInt = 342;
    char myChar[6]; 
    dtostrf(myInt, 5, 0, myChar);
    const char* sendString = myChar; 
    */

    String stringToSend = RCJ2023LCD::sendString;

    const char* sendString = stringToSend.c_str();

    int stringLength = strlen(sendString);

    Wire2.write((const uint8_t*)sendString, stringLength);
}
/*
void RCJ2023LCD::drawRect(int16_t x, int16_t y, int16_t height, int16_t width, int16_t radius, uint32_t borderColor, bool fill = false, uint32_t fillColor = BLACK){
    return;
}
*/