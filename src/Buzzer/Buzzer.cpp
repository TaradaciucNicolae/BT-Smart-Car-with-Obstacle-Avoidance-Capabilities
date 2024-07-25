#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

void init_horn_buzz(void)
{
     DDRB |= (1 << DDB0);   // PB0 ca output

}

void horn_buzz(void)
{
 

       PORTB |= (1<<PB0);

      //  PORTB = 0b1;
    
    

}

void no_horn_buzz(void)
{
  PORTB &= ~(1<<PB0);
 // PORTB = 0b0;
}