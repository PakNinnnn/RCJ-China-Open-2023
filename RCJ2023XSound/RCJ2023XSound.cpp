#include "RCJ2023XSound.h"

RCJ2023XSound::RCJ2023XSound(){

}

void RCJ2023XSound::begin(){

}

int RCJ2023XSound::getXSound(int XSoundChoice){
    float dist_t, sensity_t; 

    if(XSoundChoice == 0)       sensity_t = analogRead(FRONT_PIN);
    else if(XSoundChoice == 1)  sensity_t = analogRead(BACK_PIN);
    else if(XSoundChoice == 2)  sensity_t = analogRead(LEFT_PIN);
    else if(XSoundChoice == 3)  sensity_t = analogRead(RIGHT_PIN);
    else                        sensity_t = 0;
     

    return sensity_t;
}

