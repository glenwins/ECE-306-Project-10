//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
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

// Function Prototypes
void main(void);
void Init_Conditions(void);
void Display_Process(void);
void Init_LEDs(void);


  // Global Variables
extern char display_line[4][11];
extern char *display[4];
extern volatile unsigned char display_changed;
extern volatile unsigned int Time_Sequence;
unsigned int old_Time_Sequence;
unsigned volatile int mytime;
int clear_line;
extern char display_line[4][11];
char process_buffer0[32];
extern int timerStart;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
  
  
  PM5CTL0  &= ~LOCKLPM5;
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_Serial();
  Init_ADC();

// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], "          ");

// This line identifies the text on the Display is to change.
  display_changed = TRUE;
  
    
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run

      Glen_StateMachine();            // Run a Time Based State Machine
      Display_Process();                 // Update Display
      P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
      buffer_process();
      BLTest();
      if(timerStart)timer_display();
      
      if(process_buffer0[10] == 'I' & process_buffer0[11] == 'P'){
        displayIP();
      }
      if(Time_Sequence != old_Time_Sequence){
        mytime++;
        old_Time_Sequence = Time_Sequence;
    }
    if(mytime>time_10){
      P3OUT |= IOT_EN_CPU;
      mytime=RESET_STATE;
    }

  if((P6IN & L_FORWARD) && (P6IN & L_REVERSE)){
    Motor_Off();
    P1OUT &= ~RED_LED;
  }
  if((P6IN & R_FORWARD) && (P6IN & R_REVERSE)){
    Motor_Off();
    P1OUT &= ~RED_LED;
  }
  

  }
//------------------------------------------------------------------------------
}






