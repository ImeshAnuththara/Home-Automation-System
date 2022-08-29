#include<avr/io.h>
#define F_CPU 1000000
#include<util/delay.h>
#include <stdlib.h>

#define lcdport PORTA
#define signal PORTB
#define DDR_A DDRA
#define DDR_B DDRB
#define DDR_C DDRC
#define DDR_D DDRD
#define en 2
#define rw 1
#define rs 0



char password[1];
char lock[0];
char key;

char keycheck();

char scankey();

void lcdcmd(unsigned char cmd);

void lcdint();
unsigned char  lcd_read();

void lcddata(unsigned char data);
//void command(unsigned char cmd);
void charactersend(unsigned char character);
void String(char *characters);

int main(){

	DDR_A=0xff;
	DDR_B=0x0f;
	DDR_D=0xf0;
	
	DDR_C|=1<<0 && 1<<1;
	PORTC=0x01;
	_delay_ms(10);

	char key;

	lcdint();
	
 
	String ("ENTER PASSWORD");
	lcdcmd(0xC0);       
	 
	 
	

  for(int i=0;i<5;i++){  

		key=scankey();
		_delay_ms(1000);
        
		lcddata('*');
		
		password[i]=key;	
        
	}
	lcdcmd(0x01);
	
	if((password[0]=='1')&&(password[1]=='2')&&(password[2]=='3')&&(password[3]=='4')&&(password[4]=='5')){
	
		String ("CORRECT PASSWORD");
		
		//DDRC=0xff;
		DDR_C|=1<<0 && 1<<1;
		PORTC=0x00;
		_delay_ms(5000);
		PORTC=0x00;
		lcdcmd(0x01);
		lcdcmd(0x80);
	
		String ("LOCK? PRESS 1");
		lcdcmd(0xC0);
		 
		key=scankey();
		_delay_ms(1000);
		  

		lcddata(key);
		lock[0]=key;
		
		if(lock[0]=='1'){
		/*	DDRC=0xff;
			PORTC=0x01;
			_delay_ms(3000);
			PORTC=0x00;*/
			lcdcmd(0x01);
		
			String ("LOCKED");
			_delay_ms(1000);
			return main();
		  }
		 
	}
		
	else{
	
		String ("WRONG PASSWORD");
		DDR_C=0xff;
		//DDRC|=1<<0 && 1<<1;
			PORTC=0x03;
		//	PORTC=0x02;
			_delay_ms(3000);
			PORTC=0x00;
	 
		return main();
	 
	}
}	



char scankey(){

	char key='a';
	while(key=='a'){

		key=keycheck();   
       
	}

	return key;
}

char keycheck(){

	PORTD=0b11101111;
	_delay_ms(10);

	if((PIND&0b00000001)==0){
		_delay_ms(10);
		return '7';
	}

	if((PIND&0b00000010)==0){
		_delay_ms(10);
		return '8';
	}

	if((PIND&0b00000100)==0){
		_delay_ms(10);
		return '9';
	}
	if((PIND&0b00001000)==0){
			_delay_ms(10);
			return 'C';
	}
	
	PORTD=0b11011111;
	_delay_ms(10);
	if((PIND&0b00000001)==0){
		_delay_ms(10);
		return '4';
	}

	if((PIND&0b00000010)==0){
		_delay_ms(10);
		return '5';
	}

	if((PIND&0b00000100)==0){
		_delay_ms(10);
		return '6';

	}
	if((PIND&0b00001000)==0){
		_delay_ms(10);
		return 'B';
	}

	PORTD=0b10111111;
	_delay_ms(10);

	if((PIND&0b00000001)==0){
		_delay_ms(10);
		return '1';
	}

	if((PIND&0b00000010)==0){
		_delay_ms(10);
		return '2';
	}

	if((PIND&0b00000100)==0){
		_delay_ms(10);
		return '3';
	}
	if((PIND&0b00001000)==0){
		_delay_ms(10);
		return'A';
	}

	PORTD=0b01111111;
	_delay_ms(10);

	if((PIND&0b00000001)==0){
		_delay_ms(10);
		return '*';
	}
	if((PIND&0b00000010)==0){
		_delay_ms(10);
		return '0';
	}

	if((PIND&0b00000100)==0){
		_delay_ms(10);
		return '#';
	}
	if((PIND&0b00001000)==0){
		_delay_ms(10);
		return'D';
	}
	
	return 'a';
}

void lcdint(){
	lcdcmd(0x38);
	_delay_ms(1);
	
	lcdcmd(0x01);
	_delay_ms(1);

	lcdcmd(0x0F);
	_delay_ms(10);
	
   lcdcmd(0x82);
   _delay_ms(10);
   
   lcdcmd(0x89);
   _delay_ms(10);
   
   lcdcmd(0x01);
   _delay_ms(10);
}



void lcdcmd(unsigned char x){

	lcdport=x;
	signal=(0<<rs)|(0<<rw)|(1<<en);

	_delay_ms(1);
	signal=(0<<rs)|(0<<rw)|(0<<en);

	_delay_ms(50);

}

void lcddata(unsigned char data){

	lcdport= data;
	signal= (1<<rs)|(0<<rw)|(1<<en);

	_delay_ms(1);
	signal= (1<<rs)|(0<<rw)|(0<<en);

	_delay_ms(50);

}
unsigned char  lcd_read(){    

	signal= (1<<rs)|(1<<rw)|(1<<en);
	_delay_ms(1);

	signal= (1<<rs)|(1<<rw)|(0<<en);
	_delay_ms(50);
	}
void charactersend(unsigned char data)
{
   
   lcdport= data;
	signal= (1<<rs)|(0<<rw)|(1<<en);

	_delay_ms(1);
	signal= (1<<rs)|(0<<rw)|(0<<en);

	_delay_ms(50);
}
void String(char *characters)
{
    while(*characters > 0)
    {
        charactersend(*characters++);
    }
}
	
