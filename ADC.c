#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

unsigned int ADC_Channel = RESET_STATE;
unsigned int ADC_Left_Detect = RESET_STATE;
unsigned int ADC_Right_Detect = RESET_STATE;
unsigned int ADC_Thumb_Detect = RESET_STATE;
unsigned int ADC_Bat = RESET_STATE;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
char adc_char[4];
extern char display_line[4][11];
unsigned int DAC_data;



void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
    // ADCCTL0 Register
    ADCCTL0 = 0; // Reset
    ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
    ADCCTL0 |= ADCMSC; // MSC
    ADCCTL0 |= ADCON; // ADC ON
    
    // ADCCTL1 Register
    ADCCTL2 = 0; // Reset
    ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
    ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
    ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
    ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
    ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
    ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
    // ADCCTL1 & ADCBUSY identifies a conversion is in process
    
    // ADCCTL2 Register
    ADCCTL2 = 0; // Reset
    ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
    ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
    ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
    ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
    // ADCMCTL0 Register
    ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
    ADCMCTL0 |= ADCINCH_2; // Left_Detect (0x04) Pin 5 A5
    ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
    ADCCTL0 |= ADCENC; // ADC enable conversion.
    ADCCTL0 &= ~ADCSC; // ADC start conversion.
}


#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
      case ADCIV_NONE:
        break;
      case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
        // before its previous conversion result was read.
        break;
      case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
        break;
      case ADCIV_ADCHIIFG: // Window comparator interrupt flags
        break;
      case ADCIV_ADCLOIFG: // Window comparator interrupt flag
        break;
      case ADCIV_ADCINIFG: // Window comparator interrupt flag
        break;
      case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
        ADCCTL0 &= ~ADCENC; // Disable ENC bit.
        switch (ADC_Channel++){
          case 0x00: // Channel A2 Interrupt
            ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
            ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
            ADC_Left_Detect = ADCMEM0; // Move result into Global
            ADC_Left_Detect = ADC_Left_Detect >> 3; // Divide the result by 4
            break;
          case 0x01:
            ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
            ADCMCTL0 |= ADCINCH_4; // Enable Next channel A4
            ADC_Right_Detect = ADCMEM0; // Move result into Global
            ADC_Right_Detect = ADC_Right_Detect >> 3; // Divide the result by 4
            break;
          case 0x02:
            ADCMCTL0 &= ~ADCINCH_4; // Disable Last channel A4
            ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
            ADC_Bat = ADCMEM0; // Move result into Global
            break;
          case 0x03:
            ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
            ADCMCTL0 |= ADCINCH_2; // Enable Next channel A2
            ADC_Thumb_Detect = ADCMEM0; // Move result into Global
            ADC_Channel=0;
            break;
          default:
            break;
        }
        ADCCTL0 |= ADCENC; // Enable Conversions
        ADCCTL0 |= ADCSC;
        break;
      default:
        break;
}
}
/*
void HEXtoBCD(int hex_value){
    int value;
    for(int i=0; i < 4; i++) {
      adc_char[i] = '0';
    }
    while (hex_value > 999){
      hex_value = hex_value - 1000;
      value = value + 1;
      adc_char[0] = 0x30 + value;
    }
    value = 0;
    while (hex_value > 99){
      hex_value = hex_value - 100;
      value = value + 1;
      adc_char[1] = 0x30 + value;
    }
    value = 0;
    while (hex_value > 9){
      hex_value = hex_value - 10;
      value = value + 1;
      adc_char[2] = 0x30 + value;
    }
    adc_char[3] = 0x30 + hex_value;
}

void adc_line(char line, char location){
//-------------------------------------------------------------
    int i;
    unsigned int real_line;
    real_line = line - 1;
    for(i=0; i < 4; i++) {
    display_line[real_line][i+location] = adc_char[i];
}
}

void Init_REF(void){
    // Configure reference module
    PMMCTL0_H = PMMPW_H; // Unlock the PMM registers
    PMMCTL2 = INTREFEN; // Enable internal reference
    PMMCTL2 |= REFVSEL_2; // Select 2.5V reference
    while(!(PMMCTL2 & REFGENRDY)); // Poll till internal reference settles
    // Using a while statement is not usually recommended without an exit strategy.
    // This while statement is the suggested operation to allow the reference to settle.
}

void Init_DAC(void){
    DAC_data = 1000; // Value between 0x000 and 0x0FFF
    SAC3DAT = DAC_data; // Initial DAC data
    SAC3DAC = DACSREF_1; // Select int Vref as DAC reference
    SAC3DAC |= DACLSEL_0; // DAC latch loads when DACDAT written
    // SAC3DAC |= DACIE; // generate an interrupt
    SAC3DAC |= DACEN; // Enable DAC
    SAC3OA = NMUXEN; // SAC Negative input MUX controL
    SAC3OA |= PMUXEN; // SAC Positive input MUX control
    SAC3OA |= PSEL_1; // 12-bit reference DAC source selected
    SAC3OA |= NSEL_1; // Select negative pin input
    SAC3OA |= OAPM; // Select low speed and low power mode
    SAC3PGA = MSEL_1; // Set OA as buffer mode
    SAC3OA |= SACEN; // Enable SAC
    SAC3OA |= OAEN; // Enable OA
}
*/






