//  Glen Morris
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//  ports.c


#include "msp430.h"
#include <string.h>
#include "macros.h"

void Init_Ports(void); //Calls the port initialization functions
void Init_Port_1(void); 
void Init_Port_2(void); 
void Init_Port_3(void); 
void Init_Port_4(void); 
void Init_Port_5(void); 
void Init_Port_6(void); 
void Carlson_StateMachine(void);


void Init_Ports(void){
    Init_Port_1();
    Init_Port_2();
    Init_Port_3();
    Init_Port_4();
    Init_Port_5();
    Init_Port_6();
}  

//defines port 1 pins
void Init_Port_1(void){
    P1OUT = 0x00;
    P1DIR = 0x00;
    //P1 PIN0
    P1SEL0 &= ~RED_LED;
    P1SEL1 &= ~RED_LED;
    P1DIR |= RED_LED;
    //P1 PIN1
    P1SELC |= A1_SEEED; // ADC input for A1_SEEED
    P1SELC |= V_DETECT_L; // ADC input for V_DETECT_L
    P1SELC |= V_DETECT_R; // ADC input for V_DETECT_R
    P1SELC |= A4_SEEED; // ADC input for V_A4_SEEED
    P1SELC |= V_THUMB; // ADC input for V_THUMB
    //P1 PIN6
    P1SEL0 |= UCA0RXD;
    P1SEL1 &= ~UCA0RXD;
    //P1 PIN7
    P1SEL0 |= UCA0TXD;
    P1SEL1 &= ~UCA0TXD;
}

//defines port 2 pins
void Init_Port_2(void){ // Configure Port 2
    P2OUT = 0x00; // P2 set Low
    P2DIR = 0x00; // Set P2 direction to output
    //P2 PIN 0
    P2SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P2SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P2OUT &= ~RESET_LCD; // Initial Value = Low / Off
    P2DIR |= RESET_LCD; // Direction = output
    //P2 PIN 1
    P2SEL0 &= ~Check_Bat; // Check_Bat GPIO operation
    P2SEL1 &= ~Check_Bat; // Check_Bat GPIO operation
    P2OUT &= ~Check_Bat; // Initial Value = Low / Off
    P2DIR |= Check_Bat; // Direction = output
    //P2 PIN 2
    P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
    P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
    P2OUT &= ~IR_LED; // Initial Value = Low / Off
    P2DIR |= IR_LED; // Direction = input
    //P2 PIN 3
    P2SEL0 &= ~SW2; // SW2 Operation
    P2SEL1 &= ~SW2; // SW2 Operation
    P2OUT |= SW2; // Configure pullup resistor
    P2DIR &= ~SW2; // Direction = input
    P2REN |= SW2; // Enable pullup resistor
    P2IE  |= SW2;                    // Enable interrupts for Button2
    P2IES |= SW2;                    // Interrupts occur on Hi/Lo edge
    P2IFG &= ~SW2; 
    //P2 PIN 4
    P2SEL0 &= ~IOT_RUN_CPU; // IOT_RUN_CPU GPIO operation
    P2SEL1 &= ~IOT_RUN_CPU; // IOT_RUN_CPU GPIO operation
    P2OUT |= IOT_RUN_CPU; // Initial Value = Low / Off
    P2DIR |= IOT_RUN_CPU; // Direction = input
    //P2 PIN5
    P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2OUT |= DAC_ENB; // Initial Value = High
    P2DIR |= DAC_ENB; // Direction = output
    //P2 PIN6
    P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
    P2SEL1 |= LFXOUT; // LFXOUT Clock operation
    //P2 PIN7
    P2SEL0 &= ~LFXIN; // LFXIN Clock operation
    P2SEL1 |= LFXIN; // LFXIN Clock operation
}
                
//defines port 3 pins
void Init_Port_3(void){
    P3OUT = 0x00;
    P3DIR = 0x00;
    //P3 PIN 0
    P3SEL0 &= ~TEST_PROBE;
    P3SEL1 &= ~TEST_PROBE;
    P3DIR &= ~TEST_PROBE;
    //P3 PIN1
    P3SEL0 |= OA2O;
    P3SEL1 |= OA2O;
    //P3 PIN2
    P3SEL0 |= OA2N;
    P3SEL1 |= OA2N;
    //P3 PIN3
    P3SEL0 |= OA2P;
    P3SEL1 |= OA2P;
    //P3 PIN4
    P3SEL0 &= ~SMCLK;
    P3SEL1 &= ~SMCLK;
    P3DIR &= ~SMCLK;
    //P3 PIN5
    P3SEL0 &= ~DAC_CNTL;
    P3SEL1 &= ~DAC_CNTL;
    P3DIR &= ~DAC_CNTL;
    //P3 PIN6
    P3SEL0 &= ~IOT_LINK_CPU;
    P3SEL1 &= ~IOT_LINK_CPU;
    P3DIR |= IOT_LINK_CPU;
    P3OUT &= ~IOT_LINK_CPU;
    //P3 PIN7
    P3SEL0 &= ~IOT_EN_CPU;
    P3SEL1 &= ~IOT_EN_CPU;
    P3DIR |= IOT_EN_CPU;
    P3OUT &= ~IOT_EN_CPU;
}
            
//defines port 4 pins
void Init_Port_4(void){
    P4OUT = 0x00; // P1 set Low
    P4DIR = 0x00; // Set P1 direction to output
    // P4 PIN 0
    P4SEL0 &= ~DAC_CNTL1; // DAC_CNTL1 GPIO operation
    P4SEL1 &= ~DAC_CNTL1; // DAC_CNTL1 GPIO operation
    P4DIR &= ~DAC_CNTL1; // Set P4_0 direction to input
    // P4 PIN 1
    P4SEL0 &= ~SW1; // SW1 GPIO operation
    P4SEL1 &= ~SW1; // SW1 GPIO operation
    P4OUT |= SW1; // Configure pullup resistor
    P4DIR &= ~SW1; // Direction = input
    P4REN |= SW1; // Enable pullup resistor
    P4IES |= SW1; // P4.1 Hi/Lo edge interrupt
    P4IFG &= ~SW1; // Clear all P4.1 interrupt flags
    P4IE |= SW1; // P4.1 interrupt enabled
    // P4 PIN 2
    P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
    // P4 PIN 3
    P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
    // P4 PIN 4
    P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
    P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
    // P4 PIN 5
    P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
    P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
    // P4 PIN 6
    P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
    P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
    // P4 PIN 7
    P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
    P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
}
       
//defines port 5 pins
void Init_Port_5(void){
    P5OUT = 0x00;
    P5DIR = 0X00;
    //P5 PIN0
    P5SELC |= V_BAT; // ADC input for V_BAT
    //P5 PIN1
    P5SELC |= V_5_0; // ADC input for V_BAT
    //P5 PIN2
    P5SELC |= V_DAC; // ADC input for V_DAC
    //P5 PIN3
    P5SELC |= V_3_3; // ADC input for V_3_3
    //P5 PIN4
    P5SEL0 &= ~IOT_BOOT_CPU;
    P5SEL1 &= ~IOT_BOOT_CPU;
    P5DIR |= IOT_BOOT_CPU;
    P5OUT |= IOT_BOOT_CPU;
}

//defines port 6 pins
void Init_Port_6(void){
    P6OUT = 0x00;
    P6DIR = 0x00;
    //P6 PIN0
    P6SEL0 |= R_FORWARD;
    P6SEL1 &= ~R_FORWARD;
    P6DIR |= R_FORWARD;
    //P6 PIN1
    P6SEL0 |= R_REVERSE;
    P6SEL1 &= ~R_REVERSE;
    P6DIR |= R_REVERSE;
    //P6 PIN2
    P6SEL0 |= L_FORWARD;
    P6SEL1 &= ~L_FORWARD;
    P6DIR |= L_FORWARD;
    //P6 PIN3
    P6SEL0 |= L_REVERSE;
    P6SEL1 &= ~L_REVERSE;
    P6DIR |= L_REVERSE;
    //P6 PIN4
    P6SEL0 &= ~LCD_BACKLITE;
    P6SEL1 &= ~LCD_BACKLITE;
    P6DIR |= LCD_BACKLITE;
    P6OUT |= LCD_BACKLITE;
    //P6 PIN5
    P6SEL0 &= ~P6_5;
    P6SEL1 &= ~P6_5;
    P6DIR &= ~P6_5;
    //P6 PIN6
    P6SEL0 &= ~GRN_LED;
    P6SEL1 &= ~GRN_LED;
    P6DIR |= GRN_LED;
    P6OUT &= ~GRN_LED;
}

