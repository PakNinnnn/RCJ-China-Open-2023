#include <RCJ2023Robot.h>
#include "RCJ2023OLED.h"

#define BACK_GS1  A2
#define BACK_GS2  A1
#define BACK_GS3  A0

#define FRONT_GS1 A3
#define FRONT_GS2 A4
#define FRONT_GS3 A5

#define RIGHT_GS1 A15
#define RIGHT_GS2 A16
#define RIGHT_GS3 A17

#define LEFT_GS1  A20
#define LEFT_GS2  A21
#define LEFT_GS3  A22

#define threshold 1023

RCJ2023Robot robot;

void setup() {
  // put your setup code here, to run once:
  robot.begin(1, 1, 1, 1);
  setup_OLED();
  clearscreen();

  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  pinMode(29, OUTPUT);
}

void complexChaseBall(int attackWhichGoal, int ballUpperBound, int ballLowerBound, int ballOffset, int spd, int offset, int defenseSpdOffset){
  int ball = robot.camera.getOpenMV(0); 
  int ballDistance = robot.camera.getOpenMV(1); 
  int compassReading = robot.compass.getCompass();
  int angleOffset = 0;
  int speedOffset = 0;
  int ballChecker = analogRead(A14);

  if(ball >= ballUpperBound || ball <= ballLowerBound){
    if(ballChecker >= 200)
      robot.mtr.moveAtAngle(0, spd + 20, offset, compassReading);
    else
      robot.mtr.moveAtAngle(0, spd + 10, offset, compassReading);
  }
  else{
      angleOffset = map(ballDistance, 30, 100, ballOffset, 0);
      speedOffset = map(ballDistance, 30, 100, 15, 0);

      if(angleOffset < 0) angleOffset = 0;
      if(angleOffset > ballOffset) angleOffset = ballOffset;

      if(speedOffset < 0) speedOffset = 0;
      if(speedOffset > 20) speedOffset = 20;

      if(ball > ballLowerBound && ball <= 40)
        robot.mtr.moveAtAngle(ball + angleOffset, spd - speedOffset, offset, compassReading);
      else if (ball > 40 && ball <= 90)
        robot.mtr.moveAtAngle(ball + angleOffset, spd, offset, compassReading);
      else if(ball > 90 && ball <= 180)
        robot.mtr.moveAtAngle(ball + angleOffset, spd + defenseSpdOffset, offset, compassReading);
      else if(ball > 180 && ball <= 270)
        robot.mtr.moveAtAngle(ball - angleOffset, spd + defenseSpdOffset, offset, compassReading);
      else if (ball > 270 && ball <= 319)
        robot.mtr.moveAtAngle(ball - angleOffset, spd, offset, compassReading);
      else 
        robot.mtr.moveAtAngle(ball - angleOffset, spd - speedOffset, offset, compassReading);
  }
}

bool aimBall(int ballUpperBound, int ballLowerBound, int ballDetector, int moveForwardSpeed, int spd, int offset, int compassReading){
  int ball = robot.camera.getOpenMV(0);
  //displaystring(ball, 3, 10, 10);

  if(robot.checkBall()){
    if(ball >= ballUpperBound || ball <= ballLowerBound){
      if(analogRead(A14) >= ballDetector)
        return true;
      else
        robot.mtr.moveAtAngle(0, spd, offset, compassReading);
    }
    else if (ball < 180)
      robot.mtr.moveAtAngle(90, spd, offset, compassReading);
    else
      robot.mtr.moveAtAngle(270, spd, offset, compassReading);
  }
}

void moveToXY(int X, int Y, int range, int spd, int offset){
    float movingAngleRadian =  atan2(X - robot.getXCoordinate(), Y - robot.getYCoordinate());
    int movingAngleDegree = (movingAngleRadian * 180 / PI);

    if(movingAngleDegree < 0)   movingAngleDegree += 360;
    int compassReading = robot.compass.getCompass();

    Serial.println(movingAngleDegree);

    robot.mtr.moveAtAngle(movingAngleDegree, spd, offset, compassReading);

}

void grayscale(int spd, int offset, int compasssReading){
  if(analogRead(BACK_GS1) ==  threshold || analogRead(BACK_GS2) ==  threshold  
|| analogRead(BACK_GS3) ==  threshold )
    robot.mtr.moveAtAngle(0, spd, offset, compasssReading);
  else if (analogRead(FRONT_GS1) ==  threshold || analogRead(FRONT_GS2) ==  threshold  
|| analogRead(FRONT_GS3) ==  threshold )
    robot.mtr.moveAtAngle(180, spd, offset, compasssReading);
  else if (analogRead(LEFT_GS1) ==  threshold || analogRead(LEFT_GS2) ==  threshold  
|| analogRead(LEFT_GS3) ==  threshold )
    robot.mtr.moveAtAngle(130, spd, offset, compasssReading);
  else if (analogRead(RIGHT_GS1) ==  threshold || analogRead(RIGHT_GS2) ==  threshold  
|| analogRead(RIGHT_GS3) ==  threshold )
    robot.mtr.moveAtAngle(210, spd, offset, compasssReading);
}

void loop() {
  // put your main code here, to run repeatedly:
  int baseSpd = 45;
  int offset = 20;
  int defenseOffset = 15;
  int compassDirection = 0;
  int ballDetector = analogRead(A14);
  int ownGoal = 0;
  int opponentGoal = 1;
  robot.cameraTest();
  
  //else{
    if(robot.RUS.read_dist_cm() < 15){
      robot.mtr.moveAtAngle(140, baseSpd + 10, offset, robot.compass.getCompass());
    }
    else if(robot.LUS.read_dist_cm() < 15){
      robot.mtr.moveAtAngle(230, baseSpd + 10, offset, robot.compass.getCompass());
    }
    else if(robot.BUS.read_dist_cm() < 15){
      robot.mtr.moveAtAngle(0, baseSpd + 10, offset, robot.compass.getCompass());
    }
    
    else{ 
      if(robot.checkBall()) {
        digitalWrite(29, HIGH);
        if(robot.FUS.read_dist_cm() < 15)
          robot.mtr.moveAtAngle(0, baseSpd + 12, offset, robot.compass.getCompass());
        else
          robot.simpleChaseBall(355, 5, 50, baseSpd, offset, robot.compass.getCompass());
        //complexChaseBall(opponentGoal, 355, 5, 50, baseSpd, offset, defenseOffset);
      }
      else{
        digitalWrite(29, LOW); 
        robot.backHome(ownGoal, 50, baseSpd + 5, offset);
      }
    }
  //}
  
}
