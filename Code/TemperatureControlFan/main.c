#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define enablepoints   5
#define registerpoints 6

void Instruction(unsigned char Ins);
void characterSend(unsigned char character);
void String(char *str);
//void ADC_Read(char channel);


int main(void)
{
	DDRA = 0x00;
    DDRB = 0xFF;
    DDRC = 0x01;
    DDRD = 0xFF;
	//DDRD=0xFB;			/* PORTD as input */
	//PORTD=0b00000100;		/* Make pull up high */
	//PORTD=1<<3;
	

    _delay_ms(50);
    
    //ADMUX |=(1<<REFS0)|(1<<REFS1);
    //ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
    
	ADCSRA=0x87;           // Enable ADC, fr/128  
	ADMUX = 0x40;		   // Vref: Avcc

	float Temp;
	
    char SHOWA [3];
     

    Instruction(0x01); //Clear Screen 0x01 = 00000001
    _delay_ms(50);
    Instruction(0x38);
    _delay_ms(50);
    Instruction(0b00001111);
    _delay_ms(50);
    
    ADCSRA |=(1<<ADSC);
	
    while(1)
    {
		Temp = (ADC_Read(0)*4.88);
		Temp = (Temp/10)-10;
        
        String ("ROOM TEMPERATURE");
        Instruction(0x80 + 0x40 + 0);
        String ("TEMP(C)=");
        Instruction(0x80 + 0x40 + 8);
        itoa(Temp,SHOWA,10);
        String(SHOWA);
        String ("      ");
        Instruction(0x80 + 0);
		
		if(Temp >= 40){
			PORTC = 0x01;
			//String ("FAN ON");
			//Instruction(0x80 + 0x40 + 0);
		}else{
		
			PORTC = 0x00;}
		
			
        
    }    
}

void ADC_Read(char channel)							
{
	ADMUX = 0x40 | (channel & 0x07);   // set input channel to read 
	ADCSRA |= (1<<ADSC);               //Start ADC
	while (!(ADCSRA & (1<<ADIF)));     //interrupt flag 
	ADCSRA |= (1<<ADIF);               // Clear interrupt
	_delay_ms(1);                      // Wait a little bit 
	return ADCW;                       // Return ADC word 
}

void Instruction(unsigned char Ins)
{
    PORTB = Ins;
    PORTD &= ~ (1<<registerpoints);
    PORTD |= 1<<enablepoints;
    _delay_ms(20);
    PORTD &= ~1<<enablepoints;
    PORTB = 0;
}

void characterSend(unsigned char character)
{
    PORTB = character;
    PORTD |= 1<<registerpoints;
    PORTD |= 1<<enablepoints;
    _delay_ms(20);
    PORTD &= ~1<<enablepoints;
    PORTB = 0;
}
void String(char *str)
{
    while(*str > 0)
    {
        characterSend(*str++);
    }
}