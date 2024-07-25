#include "Lumini/Lumini.h"
#include <Arduino.h>

void FaruriPornite()
{
    DDRC |=(1<<PC5);
  // pinMode(A0,OUTPUT);
   
    PORTC =(1<<PC5);
 // digitalWrite(A0,HIGH);
}

void FaruriOprite()
{
    PORTC &= ~(1<<PC5);
    //digitalWrite(A0,LOW);
}