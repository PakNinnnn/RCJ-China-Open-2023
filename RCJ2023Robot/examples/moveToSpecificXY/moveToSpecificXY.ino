#include <RCJ2023Robot.h>

RCJ2023Robot robot;
 
void setup () { 
    robot.begin(-1, -1, 1, -1);

    robot.setInitialPoint(18, 28, 160, 200);
}


void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    
    /*
    Serial.print(FUS.read_dist_cm());
    Serial.print(" \t ");
    Serial.print(BUS.read_dist_cm());
    Serial.print(" \t ");
  
    Serial.print(robot.FUS.read_dist_cm());
    Serial.print(" \t ");
    Serial.print(robot.BUS.read_dist_cm()); 
    Serial.print(" \t ");
    */
    
    while(0){
      Serial.print(robot.getAnotherX());
      Serial.print("\t");
      Serial.println(robot.getAnotherY());
    }
    
    while(1){
      if(robot.arrivedPoint(25, 105, 2))
        break;
      else
        robot.moveToXY(25, 105, 2, 18, 20);
      
    }

    robot.mtr.stop();
    delay(2000);

    while(1){
      if(robot.arrivedPoint(130, 105, 2))
        break;
      else
        robot.moveToXY(130, 105, 2, 18, 20);
    }

    robot.mtr.stop();
    delay(2000);

    while(1){
      if(robot.arrivedPoint(130, 280, 2))
        break;
      else
        robot.moveToXY(130, 280, 2, 18, 20);
    }

    robot.mtr.stop();
    delay(2000);

    while(1){
      if(robot.arrivedPoint(25, 300, 2))
        break;
      else
        robot.moveToXY(25, 300, 2, 18, 20);
    }

    while(1){
      robot.mtr.stop();
    }

}



