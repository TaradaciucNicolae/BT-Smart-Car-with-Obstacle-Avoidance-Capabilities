#include "GearMotors.h"
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"

#define F_CPU 16000000L

void forward(int speed)
{

  //  OCR0A = 255;  // 105 - 255
  // 62.5kHz non-inverted Fast PWM Mode ( Mode 3 ) on OC0A with prescalar
  TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); // works
  TCCR0B = (1 << CS02) | (1 << CS00);

  DDRD |= (1 << PD6); // Output pemtru PD6 ( Enable Motor A)

  DDRD |= (1 << PD4); // Output pemtru PD4 ( In1) //era 6
  DDRD |= (1 << PD7); // Output pemtru PD7 ( In2)

 // DDRD |= (1 << PD5); // Output pemtru PD5 ( Enable Motor B)

  DDRD |= (1 << PD3); // Output pemtru PD2 ( In3)
  DDRD |= (1 << PD2); // Output pemtru PD2 ( In4)

  //        0b76543210
 // PORTD = 0b01110100;
  PORTD = (1 << PD6) | (1<<PD4) | (1<<PD2);



  OCR0A = speed;
 // OCR0B = speed;

  if (speed < 10)
  {

    PORTD = 0;
  }
}

void reverse(int speed)
{

  //  OCR0A = 255;  // 105 - 255
  // 62.5kHz non-inverted Fast PWM Mode ( Mode 3 ) on OC0A with prescalar
  TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); // works
  TCCR0B = (1 << CS02) | (1 << CS00);

  DDRD |= (1 << PD6); // Output pemtru PD6 ( Enable Motor A)

  DDRD |= (1 << PD4); // Output pemtru PD4 ( In1) //era 6
  DDRD |= (1 << PD7); // Output pemtru PD7 ( In2)

 // DDRD |= (1 << PD5); // Output pemtru PD5 ( Enable Motor B)

  DDRD |= (1 << PD3); // Output pemtru PD2 ( In3)
  DDRD |= (1 << PD2); // Output pemtru PD2 ( In4)

  //        0b76543210
  //PORTD = 0b11101000;
  PORTD = (1 << PD7) | ( 1<<PD6) | (1<<PD3);

  OCR0A = speed;
 // OCR0B = speed;

  if (speed < 10)
  {
    PORTD = 0;
  }
}