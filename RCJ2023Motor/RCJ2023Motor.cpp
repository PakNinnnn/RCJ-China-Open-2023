#include "RCJ2023Motor.h"

RCJ2023Motor::RCJ2023Motor(){

}

/*
    4/       \1

    3\       /2
*/


void RCJ2023Motor::begin(int d1, int d2, int d3, int d4){
    pinMode(MTR1_DIR, OUTPUT);
    pinMode(MTR1_PWM, OUTPUT);
    pinMode(MTR2_DIR, OUTPUT);
    pinMode(MTR2_PWM, OUTPUT);
    pinMode(MTR3_DIR, OUTPUT);
    pinMode(MTR3_PWM, OUTPUT);
    pinMode(MTR4_DIR, OUTPUT);
    pinMode(MTR4_PWM, OUTPUT);

    digitalWrite(MTR1_DIR, LOW);
    digitalWrite(MTR1_PWM, LOW);
    digitalWrite(MTR2_DIR, LOW);
    digitalWrite(MTR2_PWM, LOW);
    digitalWrite(MTR3_DIR, LOW);
    digitalWrite(MTR3_PWM, LOW);
    digitalWrite(MTR4_DIR, LOW);
    digitalWrite(MTR4_PWM, LOW);

    dir1 = d1;
    dir2 = d2;
    dir3 = d3;
    dir4 = d4;
}

void RCJ2023Motor::move(int m1, int m2, int m3, int m4){

    m1 *= dir1; 
    m2 *= dir2; 
    m2 *= dir3; 
    m4 *= dir4; 

    long MTR1_STATE = m1 < 0 ? HIGH : LOW;
    long MTR2_STATE = m2 < 0 ? HIGH : LOW;
    long MTR3_STATE = m3 < 0 ? HIGH : LOW;
    long MTR4_STATE = m4 < 0 ? HIGH : LOW;

    int MTR1_SPEED = m1 < 0 ? 255 - abs(m1) : m1;
    int MTR2_SPEED = m2 < 0 ? 255 - abs(m2) : m2;
    int MTR3_SPEED = m3 < 0 ? 255 - abs(m3) : m3;
    int MTR4_SPEED = m4 < 0 ? 255 - abs(m4) : m4;

    digitalWrite(MTR1_DIR,MTR1_STATE);
    digitalWrite(MTR2_DIR,MTR2_STATE);
    digitalWrite(MTR3_DIR,MTR3_STATE);
    digitalWrite(MTR4_DIR,MTR4_STATE);

    analogWrite(MTR1_PWM, MTR1_SPEED);
    analogWrite(MTR2_PWM, MTR2_SPEED);
    analogWrite(MTR3_PWM, MTR3_SPEED);
    analogWrite(MTR4_PWM, MTR4_SPEED);
}

void RCJ2023Motor::moveAtAngle(int angle, int spd, int offsetSpd, int compass){

    int vX = round( cos( ( ( angle + 40 ) * PI / 180 ) ) * ( spd ) );
    int vY = round( sin( ( ( angle + 50 ) * PI / 180 ) ) * ( spd ) ); 

    if(vX == -0)    vX = 0;
    if(vY == -0)    vY = 0;

    if(abs(vX) < 10){
        if(vX < 0)          vX = -10;
        else if(vX > 0)     vX = 10;
    }

    if(abs(vY) < 10){
        if(vY < 0)          vY = -10;
        else if(vY > 0)     vY = 10;
    }

    int leftCompensate = ( map( compass , 0 , 180 , 5 , offsetSpd  ) );
    int rightCompensate = ( map( compass , 180 + 1 , 359 , offsetSpd , 5 ) );

    //int spdCompensate = map(compass, 0, 180, 5, offsetSpd);

    if(leftCompensate < 0) leftCompensate = 0;
    if(rightCompensate < 0) rightCompensate = 0;

    if(leftCompensate > offsetSpd) leftCompensate = offsetSpd;
    if(rightCompensate > offsetSpd) rightCompensate = offsetSpd;
    
    if(compass > tolerant && compass <= 180)
        move(vX + leftCompensate, vY + leftCompensate, vX - leftCompensate * 3, vY - leftCompensate * 3);
    else if (compass > 180 && compass < 360 - tolerant)
        move(vX - rightCompensate * 3, vY - rightCompensate * 3, vX + rightCompensate, vY + rightCompensate);
    else
        move(vX, vY, vX, vY);
    

    /*
    Serial.print(compass);
    Serial.print(" ");
    Serial.print(leftCompensate);
    Serial.print(" ");
    Serial.print(rightCompensate);
    Serial.println(" "); 
    */

    //move(vX, vY, vX, vY);
}

void RCJ2023Motor::stop(){
    move(0, 0, 0, 0);
}

/*

    int end_angle = angle + 180;
    end_angle = end_angle > 359 ? end_angle - 359 : end_angle;

    int end_angle_1 = angle - 1;
    end_angle_1 = end_angle_1 < 0 ? 360 + end_angle_1 : end_angle_1;
*/