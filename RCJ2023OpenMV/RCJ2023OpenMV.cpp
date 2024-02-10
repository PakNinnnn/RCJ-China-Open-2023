#include "RCJ2023OpenMV.h"
 
void RCJ2023OpenMV::begin(){
  Serial2.begin(baudRate);
}

int16_t RCJ2023OpenMV::uartRead(){
  while(not(Serial2.available()));  
  return Serial2.read();
}

void RCJ2023OpenMV::getUartRead(){
  while (Serial2.available() != 0) {  
    Serial2.read();
  } 
  for(int i = 0; i < 2; i++ ) {
    data[i] = uartRead();
  } 
}

int16_t RCJ2023OpenMV::getOpenMV(int16_t dataChoice){
  Serial2.write(dataChoice);

  getUartRead();

  return (data[0] & 0b0000000000111111) + ((data[1] & 0b0000000000111111) << 6);
}
