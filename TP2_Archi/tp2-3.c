
#include <msp430fg4618.h>

#include "lcd.h"

#define LED1 BIT2
#define LED2 BIT1
#define LED3 BIT1

#define SW1 BIT0
#define SW2 BIT1

volatile unsigned int i;


int main(void)
{
	
	lcd_init();
	lcd_clear();
	
	P1DIR = P1DIR & !SW1;
	
	//unsigned char borne = 40;
	//unsigned int s = 0;
	//unsigned int i = 0;
	/*for(;;)
	{
		unsigned char* ptr = (unsigned char*)(s/8 + 145);
		*ptr = s%8;
		
		while ((P1IN & SW1) != 0x00);
		for(i=0;i<100;i++);
		while ((P1IN & SW1) == 0x00);
		
		//*ptr = 0x00;
		
		s = (s == (150 -145)*8 ? 0 : s + 1);
		
		lcd_fill();
		for(i=0;i<20000;i++);
		lcd_clear();
		for(i=0;i<20000;i++);
	}*/
	//unsigned char* ptr;
	
	/*ptr = (unsigned char*)0x95;
	*ptr = 0b00000100;
	ptr = (unsigned char*)0x94;
	*ptr = 0b00000010;
	ptr = (unsigned char*)0x93;
	*ptr = 0b00000001;*/
	lcd_display_number(165);
	for(;;)
	{
		
		//for(i=0;i<1000;i++);
	}
	
	return 0;
}

 
