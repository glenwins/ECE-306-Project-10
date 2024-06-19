#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"
extern char display_line[4][11];
extern volatile unsigned int incrementer;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
void ten_sec_display(void){
  if(incrementer%10==0 && incrementer%20!=0){
    P6OUT &= ~LCD_BACKLITE;
  }
  if(incrementer%20==0){
    P6OUT |= LCD_BACKLITE;
  }


}