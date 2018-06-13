/*
 * the_flasher.c
 *
 * Created: 11/30/2017 7:29:54 PM
 * Author : domya
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <string.h>

#include "I2C_slave.h"
#include "definitions.h"
#include "led_loop_driver.h"

const uint8_t ADDRESS = 0x69;
const uint8_t STARTKEY = 55;
const uint8_t COLORKEY = 2;
const uint8_t STOPKEY = 95;
int MAXDATA = 0xFF;

const uint8_t gamma8[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

uint8_t light_data[0xff];
uint8_t red[50];
uint8_t green[50];
uint8_t blue[50];
uint8_t speed;
uint8_t step;

//Function declarations
void init_io(void);
void init_timers(void);


void parse_data(uint8_t data[])
{
	
	int colorIndex = 0;
	//checks for start key
	int i;
	for (i = 0;i < MAXDATA; i++)
	{		
		//checks for start key
		if (data[i] == STARTKEY)
		{
			// checks if step and speed
			/*PORTD |= (1<<PD3);
			_delay_ms(100);
			PORTD &= (0<<PD3);*/
			
			step = data[i+1];
			speed = data[i+2];					
		}
		else if (data[i] == COLORKEY)
		{
			/*PORTD |= (1<<PD6);
			_delay_ms(100);
			PORTD &= (0<<PD6);*/
			
			//stores colors
			red[colorIndex] = data[i+1];
			green[colorIndex] = data[i+2];
			blue[colorIndex] = data[i+3];
			colorIndex++;
		}
		else if (data[i] == STOPKEY)
		{
			break;
		}
	}
	
}
void light_em_up(void)
{
	
	
	redPWM = gamma8[(255-red[0])];
	grnPWM = gamma8[(255-green[0])];
	bluPWM = gamma8[(255-blue[0])];
}
void copy_buffer(volatile uint8_t *rxbuffer)
{
	  /*PORTD |= (1<<PD3);
	  _delay_ms(100);
	  PORTD &= (0<<PD3);
	  _delay_ms(100);*/
	  int i = 0;
	  for (i = 0; i < 0xFF; ++i){
		  light_data[i] = rxbuffer[i];
	  }
	
}

void init_io(void) {
	 DDRD |= (1<<redPin); //red
	 DDRD |= (1<<bluPin); //blue
	 DDRD |= (1<<grnPin); //green
	 
	 DDRD |= (_BV(PD6) | _BV(PD5) | _BV(PD3)); //enable output pins for LED strip
	     
    ENCDDR &= ~(_BV(ENC1A_DDR) |
    _BV(ENC1B_DDR) |
    _BV(ENC2A_DDR) |
    _BV(ENC2B_DDR) |
    _BV(ENC3A_DDR) |
    _BV(ENC3B_DDR)); //setup encoder pins as input
	     
    ENCPORT |= (_BV(ENC1A_PORT) |
    _BV(ENC1B_PORT) |
    _BV(ENC2A_PORT) |
    _BV(ENC2B_PORT) |
    _BV(ENC3A_PORT) |
    _BV(ENC3B_PORT));  //enable pullups
}

void pwm_init(void)
{
	//Fast PWM mode for timers 0 and 2 (p.106)
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	
	// clear OC0A on compare match, set on BOTTOM (inverting) (p.104)
	// 255 is fully off, 0 is fully on
	TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0); // set for A0 & B0
	TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
	
	// Use clock directly, no prescaler (p.107)
	TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
	TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);
	
	// initialize counter for TIMER 0 and TIMER 2 (p.108)
	TCNT0 = 0;
	TCNT2 = 0;
}

int main(void)
{
    init_io(); //initialized LED's
	pwm_init();//V Important
	init_interrupts();//for encoders
	I2C_init(0x69); 
	
	sei(); //allows interrupts
	
    while (1) 
    {
		copy_buffer(rxbuffer);		
		parse_data(light_data);
		if(red[0]||green[0]||blue[0]){
			light_em_up();
		}
		else{
			loop_colors();
		}
	}
}

