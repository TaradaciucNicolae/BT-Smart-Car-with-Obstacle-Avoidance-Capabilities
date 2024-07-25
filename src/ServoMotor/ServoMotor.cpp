#include "ServoMotor.h"
#include "SPI.h"


volatile static uint8_t update_pwm_ready = 0;

ISR(TIMER1_OVF_vect){
	
	update_pwm_ready = 0; // ca sa ne asiguram ca putem da o noua valoare catre PWM
}

ISR(TIMER1_COMPA_vect){

	
}

void pwm_init(void){
	
	DDRB |= (1 << DDB1);   // PB1 ca output
	
	TCCR1A = (0b10 << COM1A0) | (0b00 << COM1B0) | (0b10 << WGM10);  // Clear on Compare + Set at Bottom  
																	//si WGM10 pentru Fast PWM pe 8 biti
	
	TIMSK1 = (1 << TOIE1) | (1 << OCIE1A); // timerOverFlow Enable Interrrupt si Output Compare Match Interrupt

	OCR1AH = (SEVRO_MIN & 0xFF00) >> 8;  // Output Capture Register
	OCR1AL = (SEVRO_MIN & 0x00FF);
	
	ICR1H = (PWM_TOP & 0xFF00) >> 8;    // Input Capture Register
	ICR1L = (PWM_TOP & 0x00FF);
	
	TCCR1B = (0b11 << WGM12) | (0b010 << CS10); // Wgm12 pentru Fast Pwm pe 8 biti si CS10 pentru prescaller de 8 biti
	
}

static void update_pwm(uint16_t i){
	update_pwm_ready = 1; 
	while(update_pwm_ready != 0);
	OCR1AH = (i & 0xFF00) >> 8;
	OCR1AL = (i & 0x00FF);       // modificam valoarea PWM-ului
}


void servo_set(uint16_t deg,uint16_t max_deg){

	
	float set = (float)deg / (float)max_deg; 
	
	set = (((float)SEVRO_MAX-(float)SEVRO_MIN)*set) + (float)SEVRO_MIN;
	
	uint16_t newdeg = (uint16_t)set;
	
	update_pwm(newdeg);

	_delay_ms(10);
	
}
