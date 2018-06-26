//
//  definitions.h
//  light_controller
//
//  Created by Peter MacLellan on 11/26/15.
//  Copyright (c) 2015 Wireless Club. All rights reserved.
//


/*********************************
 
 
             ----------
    PC6    -| 1     28 |-   PC5
    PD0    -| 2     27 |-   PC4
    PD1    -| 3     26 |-   PC3
    PD2    -| 4     25 |-   PC2
    PD3    -| 5     24 |-   PC1
    PD4    -| 6     23 |-   PC0
    VCC    -| 7     22 |-   GND
    GND    -| 8     21 |-   AREF
    PB6    -| 9     20 |-   AVCC
    PB7    -| 10    19 |-   PB5
    PD5    -| 11    18 |-   PB4
    PD6    -| 12    17 |-   PB3
    PD7    -| 13    16 |-   PB2
    PB0    -| 14    15 |-   PB1
             ----------
    PIN CONNECTIONS
    ---------------
    SS:     16  PB2
    MOSI:   17  PB3
    MISO:   18  PB4
    SCK:    19  PB5
    E2_BUT: 15  PB1
    E1_BUT: 14  PB0
    E3_BUT: 10  PB7
    E1_A:   23  PC0
    E1_B:   24  PC1
    E2_A:   25  PC2
    E2_B:   26  PC3
    SDA:    27  PC4
    SCL:    28  PC5
    RST:    1   PC6
    E3_A:   2   PD0
    E3_B:   3   PD1
    RED:    5   PD3 OC2B
    GREEN:  11  PD5 OC0B
    BLUE:   12  PD6 OC0A
 
    Note: color names may be inaccurate. Taken 
    from the circuit boards, depends on wiring.
    Will probably be    GND
                        GREEN
                        RED
                        BLUE
 
 *********************************/


#ifndef light_controller_definitions_h
#define light_controller_definitions_h

//Encoder Registers
#define ENCPORT PORTC
#define ENCPINS PINC
#define ENCDDR DDRC

//Encoder 1 Pins
#define ENC1A_INT PCINT8
#define ENC1A_PORT PORTC0
#define ENC1A_DDR DDC0
#define ENC1A_PIN PINC0

#define ENC1B_INT PCINT9
#define ENC1B_PORT PORTC1
#define ENC1B_DDR DDC1
#define ENC1B_PIN PINC1

//Encoder 2 Pins
#define ENC2A_INT PCINT10
#define ENC2A_PORT PORTC2
#define ENC2A_DDR DDC2
#define ENC2A_PIN PINC2

#define ENC2B_INT PCINT11
#define ENC2B_PORT PORTC3
#define ENC2B_DDR DDC3
#define ENC2B_PIN PINC3

//Encoder 3 Pins
#define ENC3A_INT PCINT12
#define ENC3A_PORT PORTC4
#define ENC3A_DDR DDC4
#define ENC3A_PIN PINC4

#define ENC3B_INT PCINT13
#define ENC3B_PORT PORTC5
#define ENC3B_DDR DDC5
#define ENC3B_PIN PINC5

//LEDs
#define redPin PD3
#define grnPin PD5
#define bluPin PD6
//LED PWM
#define redPWM OCR2B
#define grnPWM OCR0B
#define bluPWM OCR0A

#endif