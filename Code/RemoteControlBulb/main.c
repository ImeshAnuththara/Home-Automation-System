#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


char port=0;

ISR(INT0_vect)
{
//	PORTC=~PORTC;		/* Toggle PORTC */ 
//	_delay_ms(50);  	/* Software debouncing control delay */
	port = ~port;
	if (port!=0){

	PORTC &= ~(1<<7);
	//_delay_ms(1000);
	}	
	if (port==0){
	
	DDRC=1<<7;
	PORTC |= (1<<7);
	//_delay_ms(1000);
	}

}

int main(void)
{

	DDRD=0x00;			/* PORTD as input */
	//PORTD=0b00000100;		/* Make pull up high */
	PORTD=1<<3;
	
	GICR = 1<<INT0 | 1<<INT1;		/* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
	
	sei();			/* Enable Global Interrupt */
	
	while(1);
}