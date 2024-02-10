#include "RCJ2023Robot.h"

RCJ2023Robot::RCJ2023Robot(){

}

void RCJ2023Robot::begin(int d1, int d2, int d3, int d4){
    Serial.begin(9600);

    Serial.println("Initializing compass");
    compass.begin();
    Serial.println("compass -- Sucessful");

    Serial.println("Initializing OpenMV");
    camera.begin();
    Serial.println("OpenMV -- Sucessful");

    Serial.println("Initializing XSound");
    FUS.begin(23,22);
    RUS.begin(21,20);
    BUS.begin(12,38);
    LUS.begin(37,28);
    Serial.println("XSound -- Sucessful");

    Serial.println("Initializing Mtr");
    mtr.begin(d1, d2, d3, d4);
    Serial.println("Mtr -- Sucessful");

    pinMode(Button0, INPUT);
    pinMode(Button1, INPUT);

    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(13, OUTPUT);
}

void RCJ2023Robot::cameraTest(){
    Serial.print("Ball Angle: ");
    Serial.print(camera.getOpenMV(0));
    Serial.print( " | ");

    Serial.print("Y Goal Angle: ");
    Serial.print(camera.getOpenMV(2));
    Serial.print( " | ");

    Serial.print("B Goal Angle: ");
    Serial.print(camera.getOpenMV(4));
    Serial.print( " | ");

    Serial.println();
}

void RCJ2023Robot::xsoundTest(){
    Serial.print("Front: ");
    Serial.print(FUS.read_dist_cm());
    Serial.print( " | ");

    Serial.print("Back: ");
    Serial.print(BUS.read_dist_cm());
    Serial.print( " | ");

    Serial.print("Left");
    Serial.print(LUS.read_dist_cm());
    Serial.print( " | ");

    Serial.print("Right");
    Serial.print(RUS.read_dist_cm());
    Serial.print( " | ");

    Serial.println();
}

void RCJ2023Robot::motorTest(){
    mtr.move(20, 0, 0, 0);
    delay(2000);
    mtr.move(0, 20, 0, 0);
    delay(2000);
    mtr.move(0, 0, 20, 0);
    delay(2000);
    mtr.move(0, 0, 0, 20);
    delay(2000);
    mtr.move(20, 20, 20, 20);
    delay(2000);
    mtr.move(-20, -20, -20, -20);
    delay(2000);
    mtr.move(0, 0, 0, 0);
}

void RCJ2023Robot::led(int choice, long status){
    if(choice == 0)         digitalWrite(LED0, status);
    else if(choice == 1)     digitalWrite(LED1, status);
    else if(choice == 2)    digitalWrite(LED2, status);
    else                    return;
}

bool RCJ2023Robot::buttonStatus(int choice){
    return digitalRead(choice == 0 ? Button0 : Button1);
}

bool RCJ2023Robot::pressedButton0(){
    bool buttonState =  buttonStatus(0);

    if(buttonState == 1 && previousButtonState0 == 0)
        button0Pressed = true;
    else if (buttonState == 0 && previousButtonState0 == 1 && button0Pressed){
        button0Pressed = false;
  }

  previousButtonState0 = buttonState;
  
  return button0Pressed;
}

bool RCJ2023Robot::pressedButton1(){
    bool buttonState =  buttonStatus(1);

    if(buttonState == 1 && previousButtonState1 == 0)
        button1Pressed = true;
    else if (buttonState == 0 && previousButtonState1 == 1 && button1Pressed){
        button1Pressed = false;
  }

  previousButtonState1 = buttonState;
  
  return button1Pressed;
}

int RCJ2023Robot::getNewCompass(int angle){
    int myNorth = compass.getCompass() - angle;
    if(myNorth < 0)
        myNorth = myNorth + 360;
    
    return myNorth;
}

bool RCJ2023Robot::checkBall(){
    int ball = camera.getOpenMV(0);
    
    if(ball != 999) return true;
    else            return false;
}

void RCJ2023Robot::simpleChaseBall(int ballUpperBound, int ballLowerBound, int ballOffset, int spd, int offset, int compassReading){
    int ball = camera.getOpenMV(0);
    //int compassReading = compass.getCompass();
 
    if(ball >= ballUpperBound || ball <= ballLowerBound)
        mtr.moveAtAngle(0, spd, offset, compassReading);
    else if(ball > ballLowerBound && ball <= 180)
        mtr.moveAtAngle(ball + ballOffset, spd, offset, compassReading);
    else
        mtr.moveAtAngle(ball - ballOffset, spd, offset, compassReading);
}

void RCJ2023Robot::backHome(int whichGoal, int stopDistance, int spd, int offset){
    int goalAngle = whichGoal == 0 ? camera.getOpenMV(2) : camera.getOpenMV(4);
    int compassReading = compass.getCompass();
    int backXsound = BUS.read_dist_cm();

    if(backXsound < stopDistance)
        mtr.stop();
    else
        mtr.moveAtAngle(goalAngle, spd, offset, compassReading);

}

void RCJ2023Robot::complexChaseBall(int attackWhichGoal, int ballUpperBound, int ballLowerBound, int ballOffset, int spd, int offset, int defenseSpdOffset){
    //int attackingGoal = attackWhichGoal == 0 ? camera.getOpenMV(2) : camera.getOpenMV(4);
    int ball = camera.getOpenMV(0);
    int ballDistance = camera.getOpenMV(1);
    int compassReading = compass.getCompass();
    int angleOffset = 0;

    if(ball >= ballUpperBound || ball <= ballLowerBound)
        mtr.moveAtAngle(0, spd, offset, compassReading);
    else{
        angleOffset = map(ballDistance, 40, 100, ballOffset, 0);

        if(angleOffset < 0) angleOffset = 0;
        if(angleOffset > ballOffset) angleOffset = ballOffset;

        if(ball > ballLowerBound && ball <= 90)
            mtr.moveAtAngle(ball + angleOffset, spd, offset, compassReading);
        else if(ball > 90 && ball <= 180)
            mtr.moveAtAngle(ball + angleOffset, spd + defenseSpdOffset, offset, compassReading);
        else if(ball > 180 && ball <= 270)
            mtr.moveAtAngle(ball - angleOffset, spd + defenseSpdOffset, offset, compassReading);
        else 
            mtr.moveAtAngle(ball - angleOffset, spd, offset, compassReading);
    }

    /*
    Serial.print(ball);
    Serial.print(" ");
    Serial.print(camera.getOpenMV(1));
    Serial.print(" ");
    Serial.println(angleOffset);
    */
}

void RCJ2023Robot::setInitialPoint(int minX, int minY, int width, int height){
    this->minX = minX;      
    this->minY = minY; 
    this->width = width;    
    this->height = height;

    this->currentX = 0;
    this->currentY = 0;
}

int RCJ2023Robot::getXCoordinate(){
    int leftXSound = LUS.read_dist_cm();
    int rightXSound = RUS.read_dist_cm();

    //Serial.print(leftXSound);
    //Serial.print(" ");
    //Serial.println(rightXSound);

    if(leftXSound <= rightXSound)
        this->currentX = leftXSound - minX;
    else
        this->currentX = width - rightXSound + minX;

    return this->currentX;
}

int RCJ2023Robot::getYCoordinate(){
    int frontXSound = FUS.read_dist_cm();
    int backXSound = BUS.read_dist_cm();

    //Serial.print(frontXSound);
    //Serial.print(" ");
    //Serial.println(backXSound);

    if(backXSound <= frontXSound)
        this->currentY = backXSound - this->minY;
    else
        this->currentY = this->height - frontXSound + minY;

    return this->currentY;
}

void RCJ2023Robot::anotherCoordinates(){
    int X = RUS.read_dist_cm() - LUS.read_dist_cm();
    int Y = FUS.read_dist_cm() - BUS.read_dist_cm();

    //X = constrain(X, -width, width);
    //Y = constrain(Y, -height, height);

    Serial.print(X);
    Serial.print(" ");
    Serial.println(Y);
}

int RCJ2023Robot::getAnotherX(){
    return (width / 2) - (RUS.read_dist_cm()-LUS.read_dist_cm());
}

int RCJ2023Robot::getAnotherY(){
    return (height) - (FUS.read_dist_cm()-BUS.read_dist_cm());
}


bool RCJ2023Robot::arrivedPoint(int X, int Y, int range){
    if(abs(getAnotherX() - X) < range && abs(getAnotherY() - Y) < range )
        return true;
    else
        return false;
}

bool RCJ2023Robot::arrivedPointForSecond(int X, int Y, int range, int second){
    bool arrivedAtPoint = arrivedPoint(X, Y, range);
    return arrivedAtPoint;
    if(arrivedAtPoint){
        unsigned long startTime = millis();
        while(millis() - startTime < second){
            bool currentArrivedPoint = arrivedPoint(X, Y, range);
            
            if(!currentArrivedPoint){
                while(1){

                }
            } 
        }

        if(millis() - startTime >= second)
            return true;
    }

    return false;
}

void RCJ2023Robot::moveToXY(int X, int Y, int range, int spd, int offset){
    float movingAngleRadian =  atan2(X - getAnotherX(), Y - getAnotherY());
    int movingAngleDegree = (movingAngleRadian * 180 / PI);

    if(movingAngleDegree < 0)   movingAngleDegree += 360;
    int compassReading = compass.getCompass();

    //Serial.println(movingAngleDegree);

     
    mtr.moveAtAngle(movingAngleDegree, spd, offset, compassReading);

}

void RCJ2023Robot::moveForSecond(int angle, int spd, int offset, int compassReading, int second){
    unsigned long startTime = millis();

    if(int(millis() - startTime) <= second)
        mtr.moveAtAngle(angle, spd, offset, compassReading);
    else
        return;
}

void RCJ2023Robot::slightAdjust(int X, int Y, int adjustSpd, int spd, int offset, int second){
    int compassReading = compass.getCompass();
    
    while(1){
        if(getXCoordinate() < width / 2){
            if((LUS.read_dist_cm() - minX) > X )
                moveForSecond(270, adjustSpd, offset, compassReading, second);
            else
                moveForSecond(90, adjustSpd, offset, compassReading, second);
        }   
        else{
            if((RUS.read_dist_cm() - minX) > X )
                moveForSecond(90, adjustSpd, offset, compassReading, second);
            else
                moveForSecond(270, adjustSpd, offset, compassReading, second);
        } 
        break;
    }
    

    while(1){
        if(getYCoordinate() < height / 2){
            if((BUS.read_dist_cm() - minY) > Y )
                moveForSecond(180, adjustSpd, offset, compassReading, second);
            else
                moveForSecond(0, adjustSpd, offset, compassReading, second);
        }   
        else{
            if((FUS.read_dist_cm() - minY) > Y )
                moveForSecond(0, adjustSpd, offset, compassReading, second);
            else
                moveForSecond(180, adjustSpd, offset, compassReading, second);
        }
        break;
    }   
}

bool RCJ2023Robot::turnNorth(int spd, int range){
    int compassReading = compass.getCompass();
    Serial.println(compassReading);
    
    if(compassReading > range && compassReading <= 180)
        mtr.move(spd, spd, -spd, -spd);
    else if(compassReading < 359 - range && compassReading > 180)
        mtr.move(-spd, -spd, spd, spd);
    else
        return true;

    return false;
}