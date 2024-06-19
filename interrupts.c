//------------------------------------------------------------------------------
//
//  Description: This file contains the interrupts for switches and timers.
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
extern int motion_type;
volatile unsigned int incrementer;
volatile unsigned int debounce_count1;
volatile unsigned int debounce_count2;
extern char display_line[4][11];
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
int Switch1_Pressed;
int Switch2_Pressed;
int SW1_Debounce;
int SW2_Debounce;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int ADC_Thumb_Detect;
extern volatile unsigned int Time_Sequence;
volatile unsigned int Timer;
volatile unsigned int ADCTimer;
extern int emitter_on;
extern int adc_motion;
extern int baudrate;
extern int clear_line;
int IOT=0;
extern char IOTDir;
extern int timerStart;
int stopConv=0;
volatile unsigned int BLTimer;
extern int BLTimerstart;

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
  incrementer++;
  Time_Sequence++;
  ADCTimer++;
  if(BLTimerstart==ONE){
    BLTimer++;
  }
  if(stopConv==RESET_STATE && ADCTimer >= 250){
      ADCTimer = RESET_STATE;
      stopConv=ONE;
      ADCCTL0 |= ADCSC; // Enable ADC conv complete interrupt
    }
  if(timerStart)Timer++;
  
  if(incrementer>TWO){
    update_display=ONE;
    display_changed=ONE;
    incrementer=RESET_STATE;
  }


  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0

//----------------------------------------------------------------------------
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)){
  case 0: break; // No interrupt
  case 2: // CCR1 not used
    if(SW1_Debounce){
      debounce_count1++;
    }
    if(SW2_Debounce){
      debounce_count2++;
    }
    if(debounce_count1==TB0CCR1_TEN){
      P4IE |= SW1;
      P4IFG &= ~SW1;
      TB0CCTL1 &= ~CCIE;
      SW1_Debounce=RESET_STATE;
      Switch1_Pressed=RESET_STATE;
      debounce_count1=RESET_STATE;
      P6OUT |= LCD_BACKLITE;
      
    }

    if(debounce_count2==TB0CCR1_TEN){
      P2IE |= SW2;
      P2IFG &= ~SW2;
      TB0CCTL1 &= ~CCIE;
      SW2_Debounce=RESET_STATE;
      debounce_count2=RESET_STATE;
      P6OUT |= LCD_BACKLITE;
    }
    
    

  TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
break;
  case 4: // CCR2 not used
  //...... Add What you need happen in the interrupt ......
  //TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
  break;
  case 14: // overflow
  //...... Add What you need happen in the interrupt ......
break;
default: break;
}
//----------------------------------------------------------------------------
}

#pragma vector=PORT4_VECTOR
__interrupt void switch1_interrupt(void) {
    // Switch 1
    if (P4IFG & SW1) {
      debounce_count1=RESET_STATE;
      P4IFG &= ~SW1;
      SW1_Debounce=TRUE; 
      Switch1_Pressed=TRUE;
      P4IE &= ~SW1;
      TB0CCTL1 |= CCIE;
      P6OUT &= ~LCD_BACKLITE;
    }
    }

#pragma vector=PORT2_VECTOR
__interrupt void switch2_interrupt(void) {
// Switch 2
if (P2IFG & SW2) {
      debounce_count2=RESET_STATE;
      P2IFG &= ~SW2;
      SW2_Debounce=TRUE; 
      Switch2_Pressed=TRUE;
      P2IE &= ~SW2;
      TB0CCTL1 |= CCIE;
      P6OUT &= ~LCD_BACKLITE;
      
      
}
//------------------------------------------------------------------------------
}





