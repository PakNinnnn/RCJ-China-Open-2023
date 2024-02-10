#include "RCJ2023Dribbler.h"

RCJ2023Dribbler::RCJ2023Dribbler(){

}

void RCJ2023Dribbler::begin(){
    motor.attach(MOTOR_PIN);
    long int delayStartTime = millis();
    if (millis() - delayStartTime < 1000) {
        motor.writeMicroseconds(MAX_SIGNAL);
    }
    motor.writeMicroseconds(MIN_SIGNAL);
}

void RCJ2023Dribbler::spin(bool motorState, int spd){ 
    spd = spd * 10 + 1000;

    if(spd < 1000) spd = 1000;
    if(spd > 1200) spd = 1200;
 
    if(motorState == true)
        motor.writeMicroseconds(spd);
    else
        motor.writeMicroseconds(MIN_SIGNAL);
}
