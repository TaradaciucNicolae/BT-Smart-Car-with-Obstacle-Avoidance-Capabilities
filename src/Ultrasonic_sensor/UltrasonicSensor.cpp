#include <util/delay.h>
#include <avr/io.h>
#include <Serial/Serial.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

//#include <NewPing.h>

// #define TRIGGER_PIN  10  // Arduino pin tied to trigger pin on the ultrasonic sensor.
// #define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
// #define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


#define trigPin  10  // Arduino pin tied to trigger pin on the ultrasonic sensor.  // merge cu 13
#define echoPin  8  // Arduino pin tied to echo pin on the ultrasonic sensor.    // merge cu 8 sau 12
#define echoPinverify PINB5
#define echoPinverifyPin PINB
#define SetamOsauI DDRB
#define SetamHsauL PORTB
//pare ca merge bine pe pinii 10 si 8 si merge si cu init la inceput chiar

  // sa vedem pe ce pini merge bine mouse-ul 
long durataImpuls;
int distantaCalculata;

const unsigned int MAX_DIST = 23200;

void init_Ultrasonic_Sensor(void)
{	


//pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//pinMode(echoPin, INPUT); // Sets the echoPin as an Input


// //1
// ///*
 	SetamOsauI |= (1 << trigPin);  // pin 13 / pb5 / trigPin / output

 	SetamOsauI &= ~(1<<echoPin);	 // echo e input
// //*/ // asta merge asa si asa
// //1


// //2
//    	SetamOsauI |= (1 << trigPin);  // pin 12 / pb4 / trigPin / output
//     SetamHsauL &= ~(1 <<trigPin);
 	

//   //Set Echo pin as input to measure the duration of 
//   //pulses coming back from the distance sensor
//  // pinMode(ECHO_PIN, INPUT);
//   SetamOsauI &= ~(1<< echoPin);	 // echo e input

}

int distance(void)
{
	

	//1
//	/*
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durataImpuls = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distantaCalculata = durataImpuls * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print(F("\r\n Valoare distanta: "));
  Serial.println(distantaCalculata);
  return distantaCalculata;
//	*/ // asta merge asa si asa
	//1

// // 2 da peste cap servo motorul pt ca ambele vor timer1
// unsigned long t1;
//   unsigned long t2;
//   unsigned long pulse_width;
//   float cm;

//   // Hold the trigger pin high for at least 10 us
//  // digitalWrite(TRIG_PIN, HIGH);
//   SetamHsauL |= (1 <<trigPin);
//   delayMicroseconds(10);
//   //digitalWrite(TRIG_PIN, LOW);
//   SetamHsauL &= ~(1 <<trigPin);

//   // Wait for pulse on echo pin
//   while  (!(echoPinverifyPin & (1 << echoPinverify))){

//   } // daca e ==0  do nothing

//   // Measure how long the echo pin was held high (pulse width)
//   // Note: the micros() counter will overflow after ~70 min
//   t1 = micros();
//   while ((echoPinverifyPin & (1 << echoPinverify))){

//   } // daca e ==1 do nothing
//   t2 = micros();
//   pulse_width = t2 - t1;

//   // Calculate distance in centimeters and inches. The constants
//   // are found in the datasheet, and calculated from the assumed speed
//   //of sound in air at sea level (~340 m/s).
//   cm = pulse_width / 58.0;

//   // Print out results
//   if ( pulse_width > MAX_DIST ) {
//     Serial.println("Out of range");
//   } else {
//     Serial.print(cm);
//     Serial.println(" cm \t");
//   }
//   //2 da peste cap servo pt ca ambele vor timer1

  // Wait at least 60ms before next measurement
 // delay(70);


// 	 delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
//   Serial.print("Ping: ");
//   Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
//   Serial.println("cm");

}


/*
#define F_CPU 1000000UL

void init_Ultrasonic_Sensor(void)
{
	
	DDRC = 0xFF;							// Port C all output. PC0: RW		PC1: RS		PC2: E
	DDRC &= ~(1<<DDC5);						// Set Pin C5 as input to read Echo
	PORTC |= (1<<PORTC5);					// Enable pull up on C5
	PORTC &= ~(1<<PC4);						// Init C4 as low (trigger)

	PRR &= ~(1<<PRTIM1);					// To activate timer1 module
	TCNT1 = 0;								// Initial timer value
	TCCR1B |= (1<<CS10);					// Timer without prescaller. Since default clock for atmega328p is 1Mhz period is 1uS
	TCCR1B |= (1<<ICES1);					// First capture on rising edge

	PCICR = (1<<PCIE1);						// Enable PCINT[14:8] we use pin C5 which is PCINT13
	PCMSK1 = (1<<PCINT13);					// Enable C5 interrupt
	sei();									// Enable Global Interrupts
}

void distance(void){

		_delay_ms(60); 							// To allow sufficient time between queries (60ms min)
		PORTC |= (1<<PC4);						// Set trigger high
		_delay_us(10);							// for 10uS
		PORTC &= ~(1<<PC4);						// to trigger the ultrasonic module
}

ISR(PCINT1_vect) {
	if (bit_is_set(PINC,PC5)) {					// Checks if echo is high
		TCNT1 = 0;								// Reset Timer
		PORTC |= (1<<PC3);
	} else {
		uint16_t numuS = TCNT1;					// Save Timer value
		uint8_t oldSREG = SREG;
		cli();									// Disable Global interrupts
		//ClearDisplay();							// Clear Display and send cursor home
		//Write16BitToDisplayAsDec(numuS/58);		// Write Timer Value / 58 (cm). Distance in cm = (uS of echo high) / 58
		//WriteDisplay(1,0,0x20);					// Space
		//WriteDisplay(1,0,0x63);					// c
		//WriteDisplay(1,0,0x6d);					// m
		Serial.print(numuS/58);

		SREG = oldSREG;							// Enable interrupts
		PORTC &= ~(1<<PC3);						// Toggle debugging LED
	}
}



*/


//int durata;
//int distanta;

/*
#include <NewPing.h>

#include "UltrasonicSensor.h"
#ifndef F_CPU
#define F_CPU 16000000
#endif //F_CPU

static volatile uint32_t first_reading = 0;
static volatile uint32_t second_reading = 0;
static volatile uint32_t duty_cycle = 0;

#define Trigger PB4
#define Echo PB3

void HCSR04_Init(){
	cli(); //clear prior interrupts

	//Fast PWM Configuration
	DDRB |= (1<<DDB1); //set PD6 as output
	//TCCR0A = (1<<COM0A1)|(1<<COM0A0)|(1<<WGM01)|(1<<WGM00);
  TCCR0A = (1<<COM1A1)|(1<<COM1A0)|(1<<WGM12)|(1<<WGM10);
	TCCR0B |= (1<<CS01); //prescaler = 8 for timer 0
	OCR0A = 235; //10uS trigger pulse, 118uS off-time (128uS repetition rate)

	//Input Capture configuration
	//Timer 1 running in normal mode
	DDRB &= ~(1<<DDB0); //PB0 as input (ICP1)
	TCCR1B = (1<<ICNC1)|(1<<ICES1)|(1<<CS11); //noise canceling + positive edge detection for input capture and Prescaler = 8.
	sei();//enable global interrupts
	TIMSK1 |= (1<<ICIE1); //enable timer1 input capture interrupt
}

uint32_t getDistance(){
	static uint32_t echo_pulse_uS;
	static uint32_t distance_cm;
        //32768uS = 65536 clock ticks for Timer 1 with prescaler = 8
	echo_pulse_uS = (float)duty_cycle * 32768 / 65536;
	distance_cm = echo_pulse_uS * 0.034 / 2;
	return distance_cm;
}

ISR(TIMER1_CAPT_vect){
	if ((TCCR1B & (1<<ICES1)) == (1<<ICES1)){
		first_reading = ICR1;
	}
	else{
		second_reading = ICR1;
	}
	
	if (first_reading != 0 && second_reading != 0){
		duty_cycle = second_reading - first_reading;
		first_reading = 0;
		second_reading = 0;
	}
	
	TCCR1B ^= (1<<ICES1); //toggle edge detection bit
	TIFR1 = (1<<ICF1);//clear Input Capture Flag
}
*/
/*
const unsigned int max_dist = 23200;

  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;

  	char string[10];
	long count;
	double distanta;


int TimerOverflow = 0;
*/
//ISR(TIMER1_OVF_vect)
//{
//	TimerOverflow++;	/* Increment Timer Overflow count */
//}

//void init_Ultrasonic_Sensor(void)
//{

	
//	DDRC |= (1 << DDC0);  // pin 13 / pb5 / trigPin / output

//	PORTC &= ~(1<<PC0); // trigpin pe low

//DDRB &= ~(1<<DDB0); // pin 12 / pb4 / echo pin / input

	//pinMode(trigPin, OUTPUT); //Make Arduino pin 12 as OUTPUT
  	//pinMode(echoPin, INPUT); //Make Arduino pin 13 as INPUT
	
	//DDRC |= (1 << DDC0);		/* Make trigger pin as output */
	//PORTB = 0xFF;		/* Turn on Pull-up */
	
	//LCD_Init();
	//LCD_String_xy(1, 0, "Ultrasonic");
	
	//sei();			/* Enable global interrupt */
	//TIMSK1 = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	//TCCR1A = 0;		/* Set all bit to zero Normal operation */

//}

//int distance(void)
//{
//	PORTB |= (1<<PB5); // trigPin pe high
	//delay(10);
	//PORTB &= ~(1<<PB5); // trigpin pe low

	//while(PB5 == 0b0)
	//{
	//	t1 = micros();
//	}
	
//	while(PB5 != 0b0)
	//	{
	//		t2=micros();
	//	}

	//pulse_width=t2-t1;
	//cm = pulse_width / 58.0;
//		  if ( pulse_width > max_dist ) {
 //   Serial.println("Out of range");
 // } else {
  //  Serial.print(cm);
   // Serial.print(" cm \t");
 
 // }

	


//	PORTC &= ~(1<<PC0); // trigpin pe low
//	delay(2);
	//DDRC |= (1 << DDC0); // trigPin pe high
	//delay(10);
	//PORTC &= ~(1<<PC0);; // trigpin pe low

	//durata = pulseIn(DDB0, HIGH);
	//distanta = (durata*.0343)/2;  

		//PORTC |= (1<<PC0);
		//_delay_us(10);
		//PORTC &= (~(1 << PC0));
		
		//TCNT1 = 0;	/* Clear Timer counter */
	//	TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
		//TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		//TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */

		/*Calculate width of Echo by Input Capture (ICP) */
		
		//while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for rising edge */
		//TCNT1 = 0;	/* Clear Timer counter */
		//TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		//TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	//	TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
		//TimerOverflow = 0;/* Clear Timer overflow count */

		//while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for falling edge */
		//count = ICR1 + (65535 * TimerOverflow);	/* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
	//	distanta = (double)count / 466.47;
//
	//	dtostrf(distanta, 2, 2, string);/* distance to string */
	//	strcat(string, " cm   ");	/* Concat unit i.e.cm */
	//	LCD_String_xy(2, 0, "Dist = ");
	//	LCD_String_xy(2, 7, string);	/* Print distance */
	//	_delay_ms(200);

	//delay(60);
	///return distanta;
//}