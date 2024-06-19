//  Glen Morris
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//  functions.c


#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"



extern unsigned int wheel_period;
extern volatile unsigned int Time_Sequence;
extern unsigned int counter_forward;
extern unsigned int mytime;
extern char *display[4];
extern char display_line[4][11];



void Motor_Off(void);
void Forward_Motor(void);
void Reverse_Motor(void);
void Forward(void);
void Forward_Left(void);
void Forward_Right(void);
void Reverse_Left(void);
void Reverse_Right(void);


void Motor_Off(void){
  P6OUT &= ~L_FORWARD; //  Wheel off
  P6OUT &= ~R_FORWARD; //  Wheel off
  P6OUT &= ~L_REVERSE; //  Wheel off
  P6OUT &= ~R_REVERSE; //  Wheel off
}

void Forward_Motor(void){
  P6OUT |= L_FORWARD; // Wheel on
  P6OUT |= R_FORWARD; // Wheel on
}

void Forward_Left(void){
  P6OUT |= L_FORWARD; // Wheel on
}

void Forward_Right(void){
  P6OUT |= R_FORWARD; // Wheel on
}

void Reverse_Motor(void){
  P6OUT |= L_REVERSE; // Wheel on
  P6OUT |= R_REVERSE; // Wheel on
}

void Reverse_Left(void){
  P6OUT |= L_REVERSE; // Wheel on
}

void Reverse_Right(void){
  P6OUT |= R_REVERSE; // Wheel on
}

void Forward(void){
  if(!(P2IN & SW2)){
    Forward_Motor();
  }
    
    
    
  }

















