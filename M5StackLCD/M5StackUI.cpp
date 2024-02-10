#include "M5StackUI.h"

M5StackUI::M5StackUI(int16_t brightness, uint32_t backgroundColor) : M5StackLCD(brightness, backgroundColor), currentPage(0), currentX(16), currentY(38){
    Wire.begin(); 
}

void M5StackUI::pushI2CReveive(int16_t value){
    Wire.beginTransmission(SLAVE_ADDRESS); 
    Wire.write(value & 0xff); 
    Wire.write((value >> 8) & 0xff); 
    Wire.endTransmission(); 
}

void M5StackUI::pushI2CReveive_forString(const char* sendString){
    Wire.beginTransmission(SLAVE_ADDRESS);   
    int stringLength = strlen(sendString);
    Wire.write((const uint8_t*)sendString, stringLength);
    Wire.endTransmission(); 
}

int16_t M5StackUI::pullI2CRequest(int16_t numberOfByte){
    Wire.requestFrom(SLAVE_ADDRESS, numberOfByte); 
    if (Wire.available() >= 2) { 
    byte b1 = Wire.read();
    byte b2 = Wire.read();

    int16_t receivedValue = (b2 << 8) | b1;

    return receivedValue;
    }
}

String M5StackUI::pullI2CRequest_forString(int16_t numberOfByte){
    Wire.requestFrom(SLAVE_ADDRESS, numberOfByte); 
    String receivedString = "";
    while (Wire.available()) {
        receivedString += char(Wire.read());   
    } 
    return receivedString;
}

void printWrappedSqr(int32_t x, int32_t y, int32_t side, uint32_t color){
    M5.Lcd.drawRoundRect(x - 1, y - 1, side + 1, side + 1, 5, color);
    M5.Lcd.drawRoundRect(x - 2, y - 2, side + 2, side + 2, 5, color);
}

int stringToInt(String inputString){
    return inputString.toInt();
}

void M5StackUI::UI(){ 

    pushI2CReveive_forString("9999####"); 

    String receivedString = pullI2CRequest_forString(40); 
    //int data = receivedString.toInt();
    //Serial.println(strlen(receivedString.c_str()));

    if(strlen(receivedString.c_str()) <=20){
        uint16_t bgColor;
        if(receivedString.toInt() == 0)   bgColor = PURPLE;
        if(receivedString.toInt() == 1)   bgColor = RED;
        if(receivedString.toInt() == 2)   bgColor = GREEN;
        if(receivedString.toInt() == 3)   bgColor = BLUE;
        if(receivedString.toInt() == 4)   bgColor = BLACK;

        M5StackLCD::changeBgColor(bgColor);

    }

    else{
        while(resetBGColor == false){
            M5StackLCD::changeBgColor(BLACK);

            resetBGColor = true;
            break;
        }

        int index1 = receivedString.indexOf("|");
        int index2 = receivedString.indexOf("|", index1 + 1);
        int index3 = receivedString.indexOf("|", index2 + 1);
        int index4 = receivedString.indexOf("|", index3 + 1);
        int index5 = receivedString.indexOf("|", index4 + 1); 

        String printInfo[6] = {receivedString.substring(0, index1), receivedString.substring(index1 + 1, index2), receivedString.substring(index2 + 1, index3),
            receivedString.substring(index3 + 1, index4), receivedString.substring(index4 + 1, index5), receivedString.substring(index5 + 1)};
    

        uint16_t printColor;
        if(printInfo[4].toInt() == 0)   printColor = RED;
        if(printInfo[4].toInt() == 1)   printColor = GREEN;
        if(printInfo[4].toInt() == 2)   printColor = BLUE;

        if(printInfo[3].toInt() == 3)
            M5.Lcd.fillRoundRect(printInfo[1].toInt(), printInfo[2].toInt(), 72, 27, 5, BLACK);
        else
            M5.Lcd.fillRoundRect(printInfo[1].toInt(), printInfo[2].toInt(), 130, 27, 5, BLACK);
        
        M5StackLCD::print(printInfo[0].toInt(), printInfo[1].toInt(), printInfo[2].toInt(), printInfo[3].toInt(), printColor, BLACK);
    }
    /*
    switch(currentPage){
        case 0:{menu(); break;}
        case 1:{compassUI(); break;}
        case 2:{camUI(); break;}
        case 3:{distSenUI(); break;}
        case 4:{grayScaleUI(); break;}
        case 5:{kickDribUI(); break;}
        case 6:{mtrUI(); break;}
        case 7:{commUI(); break;}
        case 8:{debugUI(); break;}
    }
    */
}

void M5StackUI::menu(){
    pushI2CReveive_forString("0000####"); 
    // Send once or keep sending


    if(!menuPage){

        M5StackLCD::print("Initializing", 80, 83, 2, PINK, BLACK);

        for(int i = 0; i < 100; ++i){
             M5.Lcd.progressBar(35, 124, 250, 30, i);
            // delay(10);
        }
        M5StackLCD::clearScreen();

        //8 Squares
        M5.Lcd.fillRoundRect(16, 38, 59, 59, 5, WHITE);
        M5.Lcd.fillRoundRect(92, 38, 59, 59, 5, WHITE);
        M5.Lcd.fillRoundRect(169, 38, 59, 59, 5, WHITE);
        M5.Lcd.fillRoundRect(245, 38, 59, 59, 5, WHITE); 
        M5.Lcd.fillRoundRect(16, 136, 59, 59, 5, WHITE);
        M5.Lcd.fillRoundRect(92, 136, 59, 59, 5, WHITE);
        M5.Lcd.fillRoundRect(169, 136, 59, 59, 5, WHITE);
        M5.Lcd.fillRoundRect(245, 136, 59, 59, 5, WHITE);

        //Compass
        M5.Lcd.fillCircle(45, 67, 23, 0xBDF7); 
        M5.Lcd.fillTriangle(45, 51, 35, 60, 55, 60, WHITE);
        M5.Lcd.fillRoundRect(44, 51, 3, 33, 2, WHITE);

        //Camera
        M5.Lcd.fillRoundRect(102, 38, 39, 16, 2, 0xBDF7);
        M5.Lcd.fillRoundRect(102, 81, 39, 16, 2, 0xBDF7);
        M5.Lcd.fillCircle(122, 67, 5, ORANGE); 

        //Distance Sensor
        M5.Lcd.fillRoundRect(187, 40, 4, 55, 2, 0xBDF7);
        M5.Lcd.fillRoundRect(191, 44, 19, 21, 2, 0xBDF7);
        M5.Lcd.fillRoundRect(191, 69, 19, 21, 2, 0xBDF7);

        menuPage = true;
    }

    if(M5.BtnA.wasReleased()){ 
        printWrappedSqr(currentX, currentY, 59, BLACK);

        if(currentX == 169) currentX -= sqrXSep_middle;
        else            currentX -= sqrXSep_normal;
    }
    if(M5.BtnB.wasReleased()){ 
        printWrappedSqr(currentX, currentY, 59, BLACK);

        if(currentX == 92) currentX += sqrXSep_middle;
        else               currentX += sqrXSep_normal;
    }

    if(currentX >= 320){  
        currentX = initialBoxX;
        currentY += sqrYSep_normal;
    }

    if(currentX <= 0 && currentY == 136){  
        currentX = endingBoxX;
        currentY = initialBoxY; 
    }

    if(currentX <= 0 && currentY == 38){  
        currentX = endingBoxX;
        currentY = endingBoxY; 
    }

    if(currentY >= 200){
        currentX = initialBoxX;
        currentY = initialBoxY;
    }

    printWrappedSqr(currentX, currentY, 59, RED);
    M5.update();

    if(M5.BtnC.wasReleased()){
        if(currentX == 16 && currentY == 38)           currentPage = 1;
        else if(currentX == 92 && currentY == 38)      currentPage = 2;
        else if(currentX == 169 && currentY == 38)     currentPage = 3;
        else if(currentX == 245 && currentY == 38)     currentPage = 4;

        else if(currentX == 16 && currentY == 136)     currentPage = 5;
        else if(currentX == 92 && currentY == 136)     currentPage = 6;
        else if(currentX == 169 && currentY == 136)    currentPage = 7;
        else if(currentX == 245 && currentY == 136)    currentPage = 8;

        M5StackLCD::clearScreen();
    }
}

void drawArrow(int16_t x, int16_t y, int16_t reverse, uint32_t color){
    M5.Lcd.fillCircle(x, y, 5, color);
    M5.Lcd.drawLine(x-1, y, 98, 121, color); 
    M5.Lcd.drawLine(x, y, 99, 121, color); 
    M5.Lcd.drawLine(x + 1, y, 100, 121, color);  
}

void M5StackUI::newArrow(int& initialX, int& initialY, int angle){
    if(angle > 359) angle = 359;
    if(angle < 0)   angle = 0;

    if(angle == compassArrowInitialAngle) return;

    drawArrow(initialX, initialY, 1, 0xBDF7);  

    int radius = 53; 

    initialX = 99 + radius * cos((angle - 90) * PI / 180);
    initialY = 121 + radius * sin((angle - 90)  * PI / 180);

    drawArrow(initialX, initialY, 1, BLACK); 
    M5.Lcd.drawCircle(99, 121, 53, BLACK);  

    compassArrowInitialAngle = angle;
}



void M5StackUI::compassUI(){ 
    pushI2CReveive_forString("1111####"); 
    //Serial.println("Compass");
    if(!compassPage){  
        M5.Lcd.fillCircle(99, 121, 75, 0xBDF7);
        M5.Lcd.drawCircle(99, 121, 53, BLACK);
        M5StackLCD::print("Compass", 10, 5, 3, 0x00FF00, BLACK);

        drawArrow(compassArrowInitialX, compassArrowInitialY, 1, BLACK); 
        
        compassPage = true;
        compassArrowInitialAngle = 0;

        M5StackLCD::print("YAW", 210, 79, 3, 0x00FF00, BLACK);
        M5StackLCD::print("359", 210, 127, 5, 0XF81F, BLACK);
    }    
    /*
    for(int i = 0; i < 360; ++i){
        newArrow(compassArrowInitialX, compassArrowInitialY, i);  
        String numberStr = String(i);
        const char* charStr = numberStr.c_str();  
 
        M5.Lcd.fillRoundRect(210, 127, 85, 40, 5, BLACK);
        M5StackLCD::print(charStr, 210, 127, 5, 0XF81F, BLACK);
 
        delay(20);
    }
    */ 
    String receivedString = pullI2CRequest_forString(20); 
    int data = receivedString.toInt();
    Serial.println(data);

    newArrow(compassArrowInitialX, compassArrowInitialY, stringToInt(receivedString));  
    M5.Lcd.fillRoundRect(210, 127, 85, 40, 5, BLACK);
    M5StackLCD::print(stringToInt(receivedString), 210, 127, 5, 0XF81F, BLACK);
} 

void M5StackUI::newball(int& initialX, int& initialY, int angle){
    if(angle == cameraBallInitialAngle) return;

    M5.Lcd.fillCircle(initialX, initialY, 10, BLACK);

    int radius = 65; 

    initialX = 90 + radius * cos((angle - 90) * PI / 180);
    initialY = 120 + radius * sin((angle - 90)  * PI / 180);

    M5.Lcd.drawCircle(90, 120, 65, GREEN); 
    M5.Lcd.fillCircle(initialX, initialY, 10, ORANGE);  

    cameraBallInitialAngle = angle;
}

void M5StackUI::camUI(){
    pushI2CReveive_forString("2222####"); 

    if(!camPage){
        M5StackLCD::print("Camera", 10, 5, 3, 0x00FF00, BLACK);

        M5.Lcd.drawCircle(90, 120, 65, GREEN); 
        M5.Lcd.drawLine(91, 106, 91, 135, GREEN); 
        M5.Lcd.drawLine(76, 120, 106, 120, GREEN); 
        M5.Lcd.fillCircle(90, 55, 10, ORANGE); 

        M5.Lcd.fillRoundRect(180, 35, 120, 50, 5, BLUE);
        M5StackLCD::print("000", 183, 47, 3, BLACK, BLUE);
        M5StackLCD::print("000", 245, 47, 3, BLACK, BLUE);

        M5.Lcd.fillRoundRect(180, 100, 120, 50, 5, ORANGE);
        M5StackLCD::print("000", 183, 112, 3, BLACK, ORANGE);
        M5StackLCD::print("000", 245, 112, 3, BLACK, ORANGE);

        M5.Lcd.fillRoundRect(180, 165, 120, 50, 5, YELLOW);
        M5StackLCD::print("000", 183, 177, 3, BLACK, YELLOW);
        M5StackLCD::print("000", 245, 177, 3, BLACK, YELLOW);
         
        cameraBallInitialAngle = 0;  
        camPage = true;
    }
    /*
    for(int i = 0; i < 360; ++i){
        newball(cameraBallInitialX, cameraBallInitialY, i); 

        String numberStr = String(i);
        String numberStr_ = String(360 - i);
        const char* charStr = numberStr.c_str();
        const char* charStr_ = numberStr_.c_str();

        M5.Lcd.fillRoundRect(183, 47, 52, 27, 5, BLUE);
        M5StackLCD::print(charStr, 183, 47, 3, BLACK, BLUE);
        M5.Lcd.fillRoundRect(245, 47, 50, 27, 5, BLUE);
        M5StackLCD::print(charStr_, 245, 47, 3, BLACK, BLUE);

        delay(100);
    }
    */

    String receivedString = pullI2CRequest_forString(40); 
    int index1 = receivedString.indexOf("|");
    int index2 = receivedString.indexOf("|", index1 + 1);
    int index3 = receivedString.indexOf("|", index2 + 1);
    int index4 = receivedString.indexOf("|", index3 + 1);
    int index5 = receivedString.indexOf("|", index4 + 1); 

    String cameraData[6] = {receivedString.substring(0, index1), receivedString.substring(index1 + 1, index2), receivedString.substring(index2 + 1, index3),
        receivedString.substring(index3 + 1, index4), receivedString.substring(index4 + 1, index5), receivedString.substring(index5 + 1)};

    newball(cameraBallInitialX, cameraBallInitialY, cameraData[0].toInt());   

    M5.Lcd.fillRoundRect(183, 47, 52, 27, 5, BLUE);
    M5StackLCD::print(cameraData[0].toInt(), 183, 47, 3, BLACK, BLUE);
    M5.Lcd.fillRoundRect(245, 47, 50, 27, 5, BLUE);
    M5StackLCD::print(cameraData[1].toInt(), 245, 47, 3, BLACK, BLUE);

    M5.Lcd.fillRoundRect(183, 112, 52, 27, 5, ORANGE);
    M5StackLCD::print(cameraData[2].toInt(), 183, 112, 3, BLACK, ORANGE);
    M5.Lcd.fillRoundRect(245, 112, 50, 27, 5, ORANGE);
    M5StackLCD::print(cameraData[3].toInt(), 245, 112, 3, BLACK, ORANGE);

    M5.Lcd.fillRoundRect(183, 177, 52, 27, 5, YELLOW);
    M5StackLCD::print(cameraData[4].toInt(), 183, 177, 3, BLACK, YELLOW);
    M5.Lcd.fillRoundRect(245, 177, 50, 27, 5, YELLOW);
    M5StackLCD::print(cameraData[5].toInt(), 245, 177, 3, BLACK, YELLOW);
}

void M5StackUI::distSenUI(){
    pushI2CReveive(currentPage); 

    if(!distSenPage){

        M5StackLCD::print("distSen", 160, 80, 3, WHITE, M5StackLCD::backgroundColor);

        distSenPage = true;
    }

}

void M5StackUI::grayScaleUI(){
    //pushI2CReveive(currentPage); 

    if(!grayScalePage){

        M5StackLCD::print("grayScale", 160, 80, 3, WHITE, M5StackLCD::backgroundColor);

        grayScalePage = true;
    }

}

void M5StackUI::kickDribUI(){
    //pushI2CReveive(currentPage); 
    
    if(!kickDribPage){

        M5StackLCD::print("kickDrib", 160, 80, 3, WHITE, M5StackLCD::backgroundColor);

        kickDribPage = true;
    }

}

void M5StackUI::mtrUI(){
    //pushI2CReveive(currentPage); 
    
    if(!mtrPage){

        M5StackLCD::print("mtr", 160, 80, 3, WHITE, M5StackLCD::backgroundColor);

        mtrPage = true;
    }

}

void M5StackUI::commUI(){
    //pushI2CReveive(currentPage); 

    if(!commPage){

        M5StackLCD::print("comm", 160, 80, 3, WHITE, M5StackLCD::backgroundColor);

        commPage = true;
    }

}

void M5StackUI::debugUI(){
    //pushI2CReveive(currentPage); 

    if(!debugPage){

        M5StackLCD::print("debug", 160, 80, 3, WHITE, M5StackLCD::backgroundColor);

        debugPage = true;
    }

}

