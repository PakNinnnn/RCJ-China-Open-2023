#ifndef RCJ2023ROBOT_H
#define RCJ2023ROBOT_H

#include <RCJ2023Compass.h>
#include <RCJ2023OpenMV.h>
//#include <RCJ2023XSound.h>
#include <RCJ2023Motor.h>
#include <Uts.h>
//#include <RCJ2023Grayscale.h>

#define LED0 13 
#define LED1 49
#define LED2 50

#define Button0 47
#define Button1 48

class RCJ2023Robot{

    public:
        int minX, minY, maxX, maxY;
        int width, height;
        int currentX, currentY;
        
        int previousButtonState0 = 0;
        bool button0Pressed = false;

        int previousButtonState1 = 0;
        bool button1Pressed = false;
        
        RCJ2023Compass  compass;
        RCJ2023OpenMV   camera;
        //RCJ2023XSound   xsound;
        RCJ2023Motor    mtr;
       // RCJ2023Grayscale   gs;

        Uts FUS;
        Uts RUS;
        Uts BUS;
        Uts LUS;  

        RCJ2023Robot();
        void begin(int, int, int, int);
        void cameraTest();
        void xsoundTest();
        void motorTest();

        void led(int, long);
        bool buttonStatus(int);
        bool pressedButton0();
        bool pressedButton1();

        int getNewCompass(int);

        bool checkBall();

        //Add checkBall() manually to prevent moving at 999 degree
        void simpleChaseBall(int, int, int, int, int, int);
        //Yellow : 0 ; Blue : 1
        void backHome(int, int, int, int);

        void complexChaseBall(int, int, int, int, int, int, int);

        void setInitialPoint(int, int, int, int);
        int getXCoordinate();
        int getYCoordinate();
        int getAnotherX();
        int getAnotherY();
        void anotherCoordinates();
        bool arrivedPoint(int, int, int);
        bool arrivedPointForSecond(int, int, int, int);

        void moveToXY(int, int, int, int, int); 
        void moveForSecond(int, int, int, int, int);
        void slightAdjust(int, int, int, int, int, int);
 
        bool turnNorth(int, int);
};

#endif
