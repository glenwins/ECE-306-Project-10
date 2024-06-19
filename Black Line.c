#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"
extern int Switch1_Pressed;
extern int Switch2_Pressed;
extern int emitter_on;
extern int adc_motion;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int ADC_Thumb_Detect;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int mytime;
extern char display_line[4][11];
extern int on_line;
extern int lined_up;
int motion_type=0;

void Find_Line(){
if(Switch1_Pressed){
    
    RIGHT_FORWARD_SPEED=SPEED_10000;
    LEFT_FORWARD_SPEED=SPEED_10000;
    
    adc_motion=1;
    Switch1_Pressed=RESET_STATE;
    
  }

    if((ADC_Left_Detect>black_detect || ADC_Right_Detect>black_detect) && on_line==0 && emitter_on==1 && (RIGHT_FORWARD_SPEED>0 ||
    LEFT_FORWARD_SPEED>0 && lined_up==0)){
          
      RIGHT_FORWARD_SPEED=WHEEL_OFF;
      LEFT_FORWARD_SPEED=WHEEL_OFF;
      on_line=TRUE;
      mytime=0;
      adc_motion=0;
  }
  if(mytime>time_10 && on_line==TRUE){
      RIGHT_REVERSE_SPEED=6500;
      LEFT_REVERSE_SPEED=6500;
  }
  if(mytime>20 && on_line==TRUE){
      RIGHT_REVERSE_SPEED=WHEEL_OFF;
      LEFT_REVERSE_SPEED=WHEEL_OFF;
  }
  if(mytime>time_50 && on_line==TRUE  && lined_up==FALSE){
    RIGHT_FORWARD_SPEED=SPEED_10000;
    if(mytime>time_70 && (ADC_Left_Detect>300 || ADC_Right_Detect>300)){
      RIGHT_FORWARD_SPEED=WHEEL_OFF;
      lined_up=TRUE;
      mytime=0;
      
    }}
    if(lined_up){
      strcpy(display_line[2], "BLACK LINE");
      display_changed=TRUE;
      update_display=TRUE;
      
    }
}

void Follow_Line(){
  if(lined_up && mytime>10 && mytime<1400){
    if(ADC_Left_Detect>300 && ADC_Right_Detect>300){
      RIGHT_FORWARD_SPEED=6500;
      LEFT_FORWARD_SPEED=6500;
      motion_type=1;
    }
    if(ADC_Left_Detect>black_detect && ADC_Right_Detect<black_detect){
      RIGHT_FORWARD_SPEED==6500;
      LEFT_FORWARD_SPEED=0;
      motion_type=1;
    }
    if(ADC_Left_Detect<black_detect && ADC_Right_Detect>black_detect){
      RIGHT_FORWARD_SPEED=0;
      LEFT_FORWARD_SPEED=6500;
      motion_type=1;
    }
    if(ADC_Left_Detect<black_detect && ADC_Right_Detect<black_detect){
      RIGHT_FORWARD_SPEED=6500;
      LEFT_FORWARD_SPEED=0;
      motion_type=1;
    }
  }
    if(mytime>1400){
      RIGHT_FORWARD_SPEED=0;
      LEFT_FORWARD_SPEED=0;
    }
    if(mytime>1405 && mytime<1470){
      RIGHT_FORWARD_SPEED=6500;
      motion_type=2;
      
    }
    if(mytime>1480 && mytime<1560){
      LEFT_FORWARD_SPEED=6500;
      RIGHT_FORWARD_SPEED=6500;
    }
    if(mytime>1600){
      LEFT_FORWARD_SPEED=0;
      RIGHT_FORWARD_SPEED=0;
      motion_type=0;
    }
    
  }
  
  
  
  
