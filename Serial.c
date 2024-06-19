#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"
volatile unsigned int iot_rx_wr;
unsigned int iot_rx_rd;
unsigned int direct_iot;
volatile unsigned int usb_rx_wr;
unsigned volatile int  TX_index0;
extern unsigned volatile int mytime;
char transmission0[25]=NULL;
char volatile temp_char0;
unsigned volatile int  TX_index1;
char transmission1[20];
char volatile temp_char1;
unsigned int volatile recieve_index1;
extern char display_line[4][11];
char volatile ring_buffer1[16];
unsigned int volatile ring_index_wr_1;
unsigned int volatile ring_index_rd_1;
char volatile ring_buffer0[16];
unsigned int volatile ring_index_wr_0;
unsigned int volatile ring_index_rd_0;
extern unsigned int volatile pb_index0;
extern char process_buffer0[32];
unsigned int volatile start_transmit;
unsigned int volatile transmission_complete=0;


void Init_Serial(){
  Init_Serial_UCA0();
  Init_Serial_UCA1();
}

void Init_Serial_UCA1(){
    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
    // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
    //------------------------------------------------------------------------------
    // Configure eUSCI_A0 for UART mode
    UCA1CTLW0 = 0;
    UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA1CTLW0 &= ~UCPEN; // No Parity
    UCA1CTLW0 &= ~UCSYNC;
    UCA1CTLW0 &= ~UC7BIT;
    UCA1CTLW0 |= UCMODE_0;
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // UCA?MCTLW = UCSx + UCFx + UCOS16
    UCA1BRW = 4 ; // 115,200 baud
    UCA1MCTLW = 0x5551 ;
    UCA1CTLW0 &= ~UCSWRST ; // release from reset
    UCA1TXBUF = 0x00; // Prime the Pump
    UCA1IE |= UCRXIE; // Enable RX interrupt
    //------------------------------------------------------------------------------
}

void Init_Serial_UCA0(){
  
    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
    // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
    //------------------------------------------------------------------------------
    // Configure eUSCI_A0 for UART mode
    UCA0CTLW0 = 0;
    UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA0CTLW0 &= ~UCPEN; // No Parity
    UCA0CTLW0 &= ~UCSYNC;
    UCA0CTLW0 &= ~UC7BIT;
    UCA0CTLW0 |= UCMODE_0;
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // UCA?MCTLW = UCSx + UCFx + UCOS16
    UCA0BRW = 4 ; // 115,200 baud
    UCA0MCTLW = 0x5551 ;
    UCA0CTLW0 &= ~UCSWRST ; // release from reset
    UCA0TXBUF = 0x00; // Prime the Pump
    UCA0IE |= UCRXIE; // Enable RX interrupt
    //------------------------------------------------------------------------------
}


#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
    //-----------------------------------------------------------------------------
    // Echo back RXed character, confirm TX buffer is ready first
  unsigned int temp;

    switch(__even_in_range(UCA0IV,0x08)){
      case 0: break; // Vector 0 - no interrupt
      case 2: // Vector 2 - RXIFG
        
        temp_char0=UCA0RXBUF;
        UCA1TXBUF=temp_char0;
        
        temp = ring_index_wr_0;
        ring_buffer0[temp] = temp_char0; 
        if(temp_char0 != '\0')ring_index_wr_0++;   
        if(ring_index_wr_0>sizeof(ring_buffer0)-1)ring_index_wr_0=0;
        
        
        
        break;
      case 4: // Vector 4 - TXIFG
       if(transmission0[TX_index0] == NULL){
            UCA0IE &= ~UCTXIE;
            transmission_complete++;
            TX_index0 = 0;
            break;
          }
          UCA0TXBUF = transmission0[TX_index0];
          TX_index0++;
        break;
      default: break;
    }
//------------------------------------------------------------------------------
}

#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
//------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
    // Echo back RXed character, confirm TX buffer is ready first
    switch(__even_in_range(UCA1IV,0x08)){
      case 0: break; // Vector 0 - no interrupt
      case 2: // Vector 2 - RXIFG
        temp_char1=UCA1RXBUF;
        UCA0TXBUF=temp_char1;
        break;
      case 4: // Vector 4 - TXIFG
        switch(TX_index1){
        case 0x00:
          
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x01:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x02:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x03:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x04:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x05:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x06:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x07:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x08:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x09:
          if(transmission1[TX_index1]!=NULL){
            UCA1TXBUF=transmission1[TX_index1];}
          TX_index1++;
          break;
        case 0x0A:
          UCA1TXBUF = 0x0D;
          TX_index1++;
          break;
        case 0x0B:
          UCA1TXBUF = 0x0A;
          UCA1IE &= ~UCTXIE;
          TX_index1=0;
          break;
        default:
          break;
        }
        break;
      default: break;
    }
//------------------------------------------------------------------------------
}


