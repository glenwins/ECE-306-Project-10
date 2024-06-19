//------------------------------------------------------------------------------
//
//  Description: This file contains the IOT instructions as well as displays the IP.
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
char *findColon;
char command[16];
extern char display_line[4][11];
char colon=':';
extern char process_buffer0[32];
char *startIP;
char *startSSID;
const char quotations = '"';
char IOTDir;
extern unsigned int volatile transmission_complete;
extern char transmission0[25];
extern unsigned int volatile ring_index_wr_1;
extern unsigned int volatile ring_index_rd_1;
extern unsigned int volatile ring_index_wr_0;
extern unsigned int volatile ring_index_rd_0;
unsigned int volatile pb_index0;
extern char volatile ring_buffer0[16];
int timerStart=0;
extern int BLState;
extern volatile unsigned int BLTimer;



void commands(){
  findColon = strchr(process_buffer0,colon);
  if(findColon[1]=='w'){
    IOTDir='w';
  }
  if(findColon[1]=='a'){
    IOTDir='a';
  }
  if(findColon[1]=='s'){

    IOTDir='s';
  }
  if(findColon[1]=='d'){
    IOTDir='d';
  }
  if(findColon[1]=='q'){
    IOTDir='q';
  }
  if(findColon[1]=='0'){
    IOTDir='0';
  }
  if(findColon[1]=='1'){
    IOTDir='1';
  }
  if(findColon[1]=='2'){
    IOTDir='2';
  }
  if(findColon[1]=='3'){
    IOTDir='3';
  }
  if(findColon[1]=='4'){
    IOTDir='4';
  }
  if(findColon[1]=='5'){
    IOTDir='5';
  }
  if(findColon[1]=='6'){
    IOTDir='6';
  }
  if(findColon[1]=='7'){
    IOTDir='7';
  }
  if(findColon[1]=='8'){
    IOTDir='8';
  }
  if(findColon[1]=='x'){
    IOTDir='x';
  }
  if(findColon[1]=='l'){
    P6OUT |= LCD_BACKLITE;
  }
  if(findColon[1]=='k'){
    P6OUT &= ~LCD_BACKLITE;
  }
  
  
  
  
  
  
  IOTDrive();
  for(int i = 0; i < 15; i++){
    findColon[i] = 0;
  }
  
}

void buffer_process(){
    
    
    if(ring_index_wr_0 != ring_index_rd_0){
       process_buffer0[pb_index0] = ring_buffer0[ring_index_rd_0];
       
       pb_index0++;
       ring_index_rd_0++;
    }
    if(ring_index_rd_0 > sizeof(ring_buffer0) - 1) ring_index_rd_0 = 0;
    
    if(process_buffer0[pb_index0 - 1] == '\n'){  
        commands();
  
      if(!(strcmp(process_buffer0, "WIFI GOT IP\r\n"))){
        IOTStartup();
      }
      if(!(strcmp(process_buffer0, "OK\r\n"))){
        IOTStartup();
      }
      
      if(process_buffer0[10] == 'I' & process_buffer0[11] == 'P'){
        displayIP();
      }
      
 
      for(int i = 0; i < sizeof(process_buffer0) - 1; i++){
        process_buffer0[i] = NULL;
      }
      pb_index0 = 0;
    }
}


void IOTStartup(void){
  switch(transmission_complete){
  case IOT_Setup0:
    strcpy(transmission0, "AT+CIPMUX=1\r\n");
    UCA0IE |=  UCTXIE;             //enable TX interrupt
    break;
  case IOT_Setup1:
    strcpy(transmission0, "AT+CIPSERVER=1,8080\r\n");
    UCA0TXBUF = NULL;
    UCA0IE |= UCTXIE;
    break;
  case IOT_Setup2:
    strcpy(transmission0, "AT+CIFSR\r\n");
    UCA0TXBUF = NULL;
    UCA0IE |= UCTXIE;
    break; 
  case IOT_Setup3:
    strcpy(transmission0, "AT+CWJAP?\r\n");
    strcpy(display_line[0], " Waiting  ");
    strcpy(display_line[1], "for input ");
    UCA0TXBUF = NULL;
    UCA0IE |= UCTXIE;
    break;
  default:
    break;
  }  
  
}

void IOTDrive(void){
  
  switch(IOTDir){
  case 'w':
    RIGHT_FORWARD_SPEED=SPEED_10700;
    LEFT_FORWARD_SPEED=SPEED_12000;
    display_line[3][0]='w';
    break;
  case 's':
    RIGHT_REVERSE_SPEED=SPEED_12000;
    LEFT_REVERSE_SPEED=SPEED_12000;
    display_line[3][0]='s';
    break;
  case 'a':
    LEFT_FORWARD_SPEED=SPEED_12000;
    RIGHT_FORWARD_SPEED=SPEED_0;
    display_line[3][0]='a';
    break;
  case 'd':
    LEFT_FORWARD_SPEED=SPEED_0;
    RIGHT_FORWARD_SPEED=SPEED_12000;
    display_line[3][0]='d';
    break;
  case 'q':
    LEFT_FORWARD_SPEED=SPEED_0;
    RIGHT_FORWARD_SPEED=SPEED_0;
    LEFT_REVERSE_SPEED=SPEED_0;
    RIGHT_REVERSE_SPEED=SPEED_0;
    display_line[3][0]='q';
    break;
  case '0':
    strcpy(display_line[0], "Arrived 00");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    strcpy(display_line[3], "          ");
    timerStart=1;
    display_line[3][0]='0';
  case '1':
    strcpy(display_line[0], "Arrived 01");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='1';
    break;
    case '2':
    strcpy(display_line[0], "Arrived 02");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='2';
    break;
    case '3':
    strcpy(display_line[0], "Arrived 03");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='3';
    break;
    case '4':
    strcpy(display_line[0], "Arrived 04");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='4';
    break;
    case '5':
    strcpy(display_line[0], "Arrived 05");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='5';
    break;
    case '6':
    strcpy(display_line[0], "Arrived 06");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='6';
    break;
    case '7':
    strcpy(display_line[0], "Arrived 07");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='7';
    break;
    case '8':
    strcpy(display_line[0], "BL Start  ");
    strcpy(display_line[1], "  Glen    ");
    strcpy(display_line[2], "  Morris  ");
    display_line[3][0]='A';
    display_line[3][0]='U';
    display_line[3][0]='T';
    display_line[3][0]='O';
    RIGHT_FORWARD_SPEED=SPEED_14000;
    LEFT_FORWARD_SPEED=SPEED_11000;
    if(BLState==RESET_STATE)BLState=ONE;
    
    P2OUT |= IR_LED;
    break;
    case 'x':
      BLTimer=RESET_STATE;
      BLState=BLExit;
    break;
  default: break;
  }
}



void displayIP(void){
  startIP = strchr(process_buffer0, quotations) + 1;
  
    for(int i=0;i<20;i++){
        if(process_buffer0[14+i]!='"'){
          if(i<8){
            display_line[2][i]=process_buffer0[14+i];}
          else display_line[3][i-8]=process_buffer0[14+i];}
        else break;
  }
}














