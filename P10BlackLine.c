//------------------------------------------------------------------------------
//
//  Description: This file contains the instructions for the P10 line following and timer for the display.
//
//
//  Glen Morris
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"



extern volatile unsigned int Timer;
volatile unsigned int ones;
volatile unsigned int tens;
volatile unsigned int hundreds;
extern char display_line[4][11];
int BLState=0;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
int BLTimerstart=0;
extern volatile unsigned int BLTimer;
int leftFirst;
int rightFirst;
int linedUp=0;


void timer_display(void){
  if(Timer>=time_20){
    ones++;
    Timer-=time_20;
  }
  if(ones>=time_10){
    tens++;
    ones-=time_10;
  }
  if(tens>=time_10){
    hundreds++;
    tens-=time_10;
  }
  display_line[3][6]=hundreds+0x30;
  display_line[3][7]=tens+0x30;
  display_line[3][8]=ones+0x30;
  display_line[3][9]='s';
}

void BLTest(void){
  switch(BLState){
    case(RESET_STATE):
      break;
      
    case(BLStart):
      BLTimerstart=1;
      if(BLTimer>time_40){
        if(ADC_Left_Detect<WhiteDetect && ADC_Right_Detect<WhiteDetect){
          BLTimerstart=RESET_STATE;
          BLTimer=RESET_STATE;
          BLState=BLIntercept;
      }
      }
      break;
    case(BLIntercept):
      if(ADC_Left_Detect>BlackDetect || ADC_Right_Detect>BlackDetect){
        RIGHT_FORWARD_SPEED=SPEED_0;
        LEFT_FORWARD_SPEED=SPEED_0;
        BLTimerstart=1;
        BLState=BLTurn;
      }
      strcpy(display_line[0], "Intercept ");
      break;
    case(BLTurn):
      if(BLTimer>=FiveSeconds){
        LEFT_FORWARD_SPEED=SPEED_12000;
        RIGHT_REVERSE_SPEED=SPEED_12000;
        if(ADC_Left_Detect>BlackDetect && ADC_Right_Detect>BlackDetect){
          LEFT_FORWARD_SPEED=SPEED_0;
          RIGHT_REVERSE_SPEED=SPEED_0;
          BLTimer=RESET_STATE;
          BLState=BLTravel;
        }
        }
        
      
      
      break;
      case(BLTravel):
        if(BLTimer>FiveSeconds){
          strcpy(display_line[0], "Intercept ");
          if (ADC_Right_Detect>BlackDetect && ADC_Left_Detect>BlackDetect){
            RIGHT_FORWARD_SPEED=SPEED_10000;
            LEFT_FORWARD_SPEED=SPEED_10000;
          }
          if(ADC_Left_Detect<BlackDetect && ADC_Right_Detect>BlackDetect){
            leftFirst=1;
            LEFT_FORWARD_SPEED=SPEED_10000;
            RIGHT_FORWARD_SPEED=SPEED_0;
          }
          if(ADC_Right_Detect<BlackDetect && ADC_Left_Detect>BlackDetect){
            rightFirst=1;
            LEFT_FORWARD_SPEED=SPEED_0;
            RIGHT_FORWARD_SPEED=SPEED_10000;
          }
          if (ADC_Right_Detect<BlackDetect && ADC_Left_Detect<BlackDetect && rightFirst){
            LEFT_FORWARD_SPEED=SPEED_10000;
            RIGHT_FORWARD_SPEED=SPEED_0;
            rightFirst=RESET_STATE;
          }
          if (ADC_Right_Detect<BlackDetect && ADC_Left_Detect<BlackDetect && leftFirst){
            LEFT_FORWARD_SPEED=SPEED_0;
            RIGHT_FORWARD_SPEED=SPEED_10000;
            leftFirst=RESET_STATE;
          }
         
          if (ADC_Right_Detect<WhiteDetect && ADC_Left_Detect<WhiteDetect){
            leftFirst=RESET_STATE;
            rightFirst=RESET_STATE;
            LEFT_FORWARD_SPEED=SPEED_0;
            RIGHT_FORWARD_SPEED=SPEED_0;
            BLTimer=RESET_STATE;
            BLState=BLCircle;
          }
        }
        break;
      case(BLCircle):
        if(BLTimer>FiveSeconds){
          strcpy(display_line[0], "BL Circle ");
          if(linedUp==RESET_STATE){
            RIGHT_REVERSE_SPEED=SPEED_10000;
            LEFT_FORWARD_SPEED=SPEED_10000;}
        
          if(ADC_Right_Detect>BlackDetect && ADC_Left_Detect>BlackDetect){
            RIGHT_REVERSE_SPEED=SPEED_0;
            LEFT_FORWARD_SPEED=SPEED_0;
            linedUp=1;
          }
          if(BLTimer>time_150){
            if (ADC_Right_Detect>BlackDetect && ADC_Left_Detect>BlackDetect){
              RIGHT_FORWARD_SPEED=SPEED_10000;
              LEFT_FORWARD_SPEED=SPEED_10000;
            }
            if(ADC_Left_Detect<BlackDetect && ADC_Right_Detect>BlackDetect){
              LEFT_FORWARD_SPEED=SPEED_10000;
              RIGHT_FORWARD_SPEED=SPEED_0;
            }
            if(ADC_Right_Detect<BlackDetect && ADC_Left_Detect>BlackDetect){
              LEFT_FORWARD_SPEED=SPEED_0;
              RIGHT_FORWARD_SPEED=SPEED_10000;
            }
            if (ADC_Right_Detect<BlackDetect && ADC_Left_Detect<BlackDetect){
              LEFT_FORWARD_SPEED=SPEED_0;
              RIGHT_FORWARD_SPEED=SPEED_10000;
            }
          }
        }
        break;
        case(BLExit):
          LEFT_FORWARD_SPEED=SPEED_0;
          RIGHT_FORWARD_SPEED=SPEED_0;
          if(BLTimer>FiveSeconds){
            strcpy(display_line[0], "BL Exit   ");
            if(BLTimer>FiveSeconds && BLTimer<time_120){
              LEFT_FORWARD_SPEED=SPEED_12000;
              RIGHT_FORWARD_SPEED=SPEED_0;
            }
            if(BLTimer>time_130 && BLTimer<time_170){
              LEFT_FORWARD_SPEED=SPEED_10000;
              RIGHT_FORWARD_SPEED=SPEED_10000;}
            if(BLTimer>time_180){
              LEFT_FORWARD_SPEED=SPEED_0;
              RIGHT_FORWARD_SPEED=SPEED_0;
              BLState=BLStop;
            }
          }
          break;
        case(BLStop):
          strcpy(display_line[0], "BL Stop   ");
          strcpy(display_line[1], "I WILL NOW");
          strcpy(display_line[2], "HAPPY CRY ");
          break;
          
    default: break;
    
      
    
    
  }
  
  
  
}

















