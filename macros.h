//  Glen Morris
//  August 24 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//  macros.h

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //
#define FALSE                (0)
#define TEST_PROBE           (0x01) // 3.0 TEST PROBE
#define RED_LED                (0x01) // 1.0 RED LED 0
#define GRN_LED                (0x40) // 6.6 GREEN LED

// IOT
#define IOT_Setup0      (0)
#define IOT_Setup1      (1)
#define IOT_Setup2      (2)
#define IOT_Setup3      (3)


// Main
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //
#define TEST_PROBE           (0x01) // 3.0 TEST PROBE
#define RED_LED                (0x01) // 1.0 RED LED 0
#define GRN_LED                (0x40) // 6.6 GREEN LED
#define fifty                   (50)
#define twenty                  (20)


// P10 Black Line
#define BLStart         (1)
#define BLIntercept     (2)
#define BLTurn          (3)
#define BLTravel        (4)
#define BLCircle        (5)
#define BLExit          (6)
#define BLStop          (7)
#define WhiteDetect     (45)
#define BlackDetect     (60)
#define FiveSeconds     (100)
#define SPEED_14000     (14000)
#define SPEED_12000     (12000)
#define SPEED_11000     (11000)
#define SPEED_10000     (10000)
#define SPEED_10700     (10700)
#define SPEED_0         (0)



// Numbers
#define ZERO                    (0)
#define ONE     (1)
#define TWO     (2)
#define TEN     (10)
#define HUNDRED (100)
#define THOUSAND        (1000)
#define ASCII_THIRTY  (0x30)

// Switches
#define PRESSED                (0)
#define RELEASED               (1)
#define NOT_OKAY               (0)
#define OKAY                   (1)
#define DEBOUNCE_TIME          (12)
#define DEBOUNCE_RESTART       (0)

// Interupt Intervals
#define TB0CCR0_INTERVAL (25000)
#define TB0CCR1_INTERVAL (50000)
#define TB0CCR1_TEN      (10)

// PWM
#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define RIGHT_REVERSE_SPEED (TB3CCR2)
#define LEFT_FORWARD_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)
#define WHEEL_OFF       (0)
#define WHEEL_PERIOD    (50010)
#define SPEED_5000      (5000)
#define SPEED_10000      (10000)


// Serial
#define BEGINNING               (0)
#define SMALL_RING_SIZE         (16)

// Timers
#define time_10         (10)
#define time_20         (20)
#define time_30         (30)
#define time_40         (40)
#define time_50         (50)
#define time_60         (60)
#define time_70         (70)
#define time_80         (80)
#define time_90         (90)
#define time_110        (110)
#define time_120        (120)
#define time_130        (130)
#define time_140        (140)
#define time_150        (150)
#define time_160        (160)
#define time_170        (170)
#define time_180        (180)


// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define A4_SEEED (0x10) // 4 A4_SEEED
#define V_THUMB (0x20) // 5 V_THUMB
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define RESET_LCD (0x01) // 0 RESET LCD
#define Check_Bat (0x02) // 1 Check ADC Voltages
#define IR_LED (0x04) // 2 IR_LED
#define SW2 (0x08) // 3 SW2
#define IOT_RUN_CPU (0x10) // 4 IOT_RUN_CPU
#define DAC_ENB (0x20) // 5 DAC_ENB
#define LFXOUT (0x40) // 6 XOUTR
#define LFXIN (0x80) // 7 XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define OA2O (0x02) // 1 OA2O
#define OA2N (0x04) // 2 OA2N
#define OA2P (0x08) // 3 OA2P
#define SMCLK (0x10) // 4 SMCLK
#define DAC_CNTL (0x20) // 5 DAC signal from Processor
#define IOT_LINK_CPU (0x40) // 6 IOT_LINK_CPU
#define IOT_EN_CPU (0x80) // 7 IOT_EN_CPU

// Port 4 Pins
#define DAC_CNTL1 (0x01) // 0 DAC_CNTR1
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

//Port 5 Pins
#define V_BAT (0X01) // 0 
#define V_5_0 (0x02) // 1
#define V_DAC (0X04) // 2 
#define V_3_3 (0X08) // 3
#define IOT_BOOT_CPU (0x10) // 4 

//Port 6 Pins
#define R_FORWARD (0X01) // 0 Right side Forward
#define R_REVERSE (0X02) // 1 Left side Forward
#define L_FORWARD (0X04) // 2 Right side Reverse
#define L_REVERSE (0X08) // 3 Left side Reverse
#define LCD_BACKLITE (0x10) // 4 
#define P6_5 (0x20) // 5 
#define GRN_LED (0x40) // 6 