#ifndef LED_LOOP_DRIVER_H
#define LED_LOOP_DRIVER_H

//Function declarations
void init_timers(void);
void init_interrupts(void);
void hsi2rgb(float H, float S, float I, int* rgb);
void loop_colors(void);


#endif //LED_LOOP_DRIVER
