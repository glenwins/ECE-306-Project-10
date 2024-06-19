#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"



extern int Switch1_Pressed;
extern int Switch2_Pressed;
extern int Switch_Counter1;
extern int Switch_Counter2;
int okay_to_look_at_switch1=1;
int count_debounce_SW1;
int sw1_position=1;
int okay_to_look_at_switch2=1;
int count_debounce_SW2;
int sw2_position=1;
extern volatile unsigned int debounce_count1;
extern volatile unsigned int debounce_count2;

void Switches_Process(void){
    Switch1_Process();
    Switch2_Process();
}

void Switch1_Process(void){

  if (okay_to_look_at_switch1 && sw1_position){
    if (!(P4IN & SW1)){
      sw1_position = PRESSED;
      okay_to_look_at_switch1 = NOT_OKAY;
      debounce_count1 = DEBOUNCE_RESTART;
      // do what you want with button press
      Switch1_Pressed=1;
    }
  }
  if (debounce_count1 <= DEBOUNCE_TIME && debounce_count1!=0){
    P6OUT &= ~LCD_BACKLITE;
  }
  else{
    if(debounce_count2==0){
      P6OUT |= LCD_BACKLITE;}
    okay_to_look_at_switch1 = OKAY;
    if (P4IN & SW1){
      sw1_position = RELEASED;
      Switch1_Pressed=0;  
      debounce_count1 = DEBOUNCE_RESTART;
  }
  }

}

void Switch2_Process(void){

  if (okay_to_look_at_switch2 && sw2_position){
    if (!(P2IN & SW2)){
      sw2_position = PRESSED;
      okay_to_look_at_switch2 = NOT_OKAY;
      debounce_count2 = DEBOUNCE_RESTART;
      // do what you want with button press
      Switch2_Pressed=1;      
  }
  }
  if (debounce_count2 <= DEBOUNCE_TIME && debounce_count2!=0){
    P6OUT &= ~LCD_BACKLITE;
  }
  else{
    if(debounce_count1==0 ){
      P6OUT |= LCD_BACKLITE;}
    okay_to_look_at_switch2 = OKAY;
    if (P2IN & SW2){
      sw2_position = RELEASED;
      Switch2_Pressed=0;  
      debounce_count2 = DEBOUNCE_RESTART;
  }
  }
}