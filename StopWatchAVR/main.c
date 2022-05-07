#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

/*Function prototypes*/
void sevenSegment_Init(void); // Function to initialize 6-digit seven segment
void Timer1_CTC_Init(void); // Function to initialize timer1 and configure it in CTC mode
void displaySegments(void); // Function to display stopwatch time on seven segment
void Reset_INT0_Init(void); // Function to initialize reset button interrupt
void Pause_INT1_Init(void); // Function to initialize pause button interrupt
void Resume_INT2_Init(void); // Function to initialize resume button interrupt

/*Global variables*/
unsigned char seconds = 0, minutes = 0, hours = 0;

/*ISRs (Interrupt handlers)*/

// Increment stopwatch
ISR(TIMER1_COMPA_vect){
	seconds++;
	if(seconds == 60){
		minutes++;
		seconds=0;
	}
	if(minutes == 60){
		hours++;
		minutes=0;
	}
	if(hours == 60){
		hours =0;
		minutes = 0;
		seconds =0;
	}
}

// Reset button
ISR(INT0_vect){
	seconds = 0;
	minutes = 0;
	hours = 0;
}

// Pause button
ISR(INT1_vect){
	TCCR1B &=~ ((1<<CS11) | (1<<CS10) | (1<<CS12));
}

// Resume button
ISR(INT2_vect){
	TCCR1B |=  (1<<CS10) | (1<<CS12);
}

/* Main Function*/
int main(void){
sevenSegment_Init();
SREG |= 1<<7;
Reset_INT0_Init();
Pause_INT1_Init();
Resume_INT2_Init();
Timer1_CTC_Init();
	while(1){
		displaySegments();
	}
	return 0;
}

void sevenSegment_Init(void){
	DDRA |= 0x3F;
	DDRC |= 0x0F;
	PORTC = 0;
}

void Timer1_CTC_Init(void){
	/*
	  F_CPU = 1Mhz, PRESCALAR = 1024
	  TICK TIME = 1024us
	  We want 1 second
	  1s/1024us = 976, 976 is the compare value in OCR1A
	 */
	TCNT1 = 0;
	OCR1A = 976; // COMPARE VALUE FOR 1 SECOND
	TIMSK |= 1<<OCIE1A; //ENABLE INTERRUPT
	TCCR1A |= 1<<FOC1A; // NON PWM MODE
	TCCR1B |= 1<<WGM12 | 1<<CS12 | 1<<CS10; // CTC MODE WITH 1024 PRESCALE
}

void Reset_INT0_Init(void){
	DDRD &=~ 1<<PD2; //INPUT PIN
	PORTD |= 1<<PD2; // ENABLE INTERNAL PULL UP
	GICR |= 1<<INT0; // ENABLE INTERRUPTS FOR INT0
	MCUCR |= 1<<ISC01; // FALLING EDGE
}

void Pause_INT1_Init(void){
	GICR |= 1<<INT1; // ENABLE INTERRUPTS FOR INT1
	MCUCR |= 1<<ISC10 | 1<<ISC11; // RISING EDGE
}


void Resume_INT2_Init(void){
	DDRB &=~ 1<<PB2; // INPUT PIN
	PORTB |= 1<<PB2; // ENABLE INTERNAL PULL UP
	GICR |= 1<<INT2; // ENABLE INTERRUPTS FOR INT2
	MCUCSR &=~ 1<<ISC2; // FALLING EDGE
}

void displaySegments(void){
	// Extracting first digit in seconds and displaying it
	PORTA = 1<<0;
	PORTC = seconds%10;

	_delay_us(30);

	// Extracting second digit in seconds and displaying it
	PORTA= 1<<1;
	PORTC = seconds/10;

	_delay_us(30);

	// Extracting first digit in minutes and displaying it
	PORTA= 1<<2;
	PORTC = minutes%10;

	_delay_us(30);

	// Extracting second digit in minutes and displaying it
	PORTA= 1<<3;
	PORTC = minutes/10;

	_delay_us(30);

	// Extracting first digit in hours and displaying it
	PORTA= 1<<4;
	PORTC = hours%10;

	_delay_us(30);

	// Extracting second digit in hours and displaying it
	PORTA= 1<<5;
	PORTC = hours/10;

	_delay_us(30);
}
