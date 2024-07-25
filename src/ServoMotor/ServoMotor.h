#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PWM_TOP (39999u) // 
#define SEVRO_MIN (1999u) // 
#define SEVRO_MAX  (4999u) //


void pwm_init(void);

void servo_set(uint16_t deg,uint16_t max_deg);
