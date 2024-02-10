#ifndef RCJ2023Grayscale_CPP
#define RCJ2023Grayscale_CPP

#include "RCJ2023Grayscale.h"

RCJ2023Grayscale::RCJ2023Grayscale(){

}

void RCJ2023Grayscale::begin(){

}

bool RCJ2023Grayscale::checkWhiteline(int dir){
    switch(dir){
    case 0:
      if(LEFT_GS1 >= threshold||LEFT_GS2 >= threshold||LEFT_GS3 >= threshold)
             return true;
        else
             return false;
    break;
    case 1:
      if(RIGHT_GS1 >= threshold||RIGHT_GS2 >= threshold||RIGHT_GS3 >= threshold)
            return true;
        else
            return false;
    break;
    case 2:
      if(BACK_GS1 >= threshold||BACK_GS2 >= threshold||BACK_GS3 >= threshold)
            return true;
        else
             return false;
    break;
    case 3:
      if(FRONT_GS1 >= threshold||FRONT_GS2 >= threshold||FRONT_GS3 >= threshold)
            return true;
        else
            return false;
    break;
    }
}

int RCJ2023Grayscale::getGrayscale(int dir, int no){
  switch (dir){
    case 0:
      switch(no){
        case 1:
          return analogRead(FRONT_GS1);
        break;
        case 2:
          return analogRead(FRONT_GS2);
        break;
        case 3:
          return analogRead(FRONT_GS3);
        break;
      }
    break; 

    case 1:
      switch(no){
        case 1:
          return analogRead(RIGHT_GS1);
        break;
        case 2:
          return analogRead(RIGHT_GS2);
        break;
        case 3:
          return analogRead(RIGHT_GS3);
        break;
      }
    break; 

    case 2:
      switch(no){
        case 1:
          return analogRead(LEFT_GS1);
        break;
        case 2:
          return analogRead(LEFT_GS2);
        break;
        case 3:
          return analogRead(LEFT_GS3);
        break;
      }
    break;

    case 3:
      switch(no){
        case 1:
          return analogRead(BACK_GS1);
        break;
        case 2:
          return analogRead(BACK_GS2);
        break;
        case 3:
          return analogRead(BACK_GS3);
        break;
      }
    break;
    
  }
}


#endif