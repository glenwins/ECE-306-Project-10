#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"
extern volatile unsigned int incrementer;
extern char display_line[4][11];
extern int Switch1_Pressed;
extern int Switch2_Pressed;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

void Move_Motor(void){
  if(Switch1_Pressed==1){
  
  switch(incrementer){
    case(30):
        strcpy(display_line[0], "          ");
        strcpy(display_line[1], " Forward  ");
        strcpy(display_line[2], "          ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
        Display_Process();
        update_display = TRUE;
        Forward_Motor();
      break;
    case(40):
      Motor_Off();
      break;
    case(50):
        strcpy(display_line[0], "          ");
        strcpy(display_line[1], " Reverse  ");
        strcpy(display_line[2], "          ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
        update_display = TRUE;
      Reverse_Motor();
      break;
    case(70):
      Motor_Off();
      break;
    case(80):
        strcpy(display_line[0], "          ");
        strcpy(display_line[1], " Forward  ");
        strcpy(display_line[2], "          ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
        update_display = TRUE;

      Forward_Motor();
      break;
     
    case(90):
      Motor_Off();
      break;
      
    case(100):
        strcpy(display_line[0], "          ");
        strcpy(display_line[1], "   Spin   ");
        strcpy(display_line[2], "Clockwise ");
        strcpy(display_line[3], "          ");
        update_display = TRUE;
        display_changed = TRUE;
      P6OUT |= L_REVERSE; // Wheel on
      P6OUT |= R_FORWARD; // Wheel on
      break;
      
    case(130):
      Motor_Off();
      break;
    
    case(150):
        strcpy(display_line[0], "   Spin   ");
        strcpy(display_line[1], " Counter  ");
        strcpy(display_line[2], "Clockwise ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
        update_display = TRUE;
      P6OUT |= R_REVERSE; // Wheel on
      P6OUT |= L_FORWARD; // Wheel on
      break;
      
    case(180):
      Motor_Off();
      break;
      
     
  }
    
    
  }
  
  
  
  
}