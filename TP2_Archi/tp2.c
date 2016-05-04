
#include <msp430fg4618.h>

//#define P5OUT   (  *((volatile unsigned char*) 0x31)  )
//#define P5DIR   (  *((volatile unsigned char*) 0x32)  )

#define LED1 0x04
#define LED2 0x02
#define LED3 0x02

#define SW1 0x01   
#define SW2 0x02

volatile unsigned int i;

int main(void)
{
	// set P5.1 to output direction
	P5DIR = LED3;
	
	P2DIR = P2DIR | (LED1 | LED2);
	P1DIR = P1DIR & !(SW1 | SW2);
	
	// turn LEDs on
	P5OUT = LED3;
	P2OUT = LED1 | LED2;
	
	while((P1IN & SW1) != 0x00 && (P1IN & SW2) != 0x00);
	
	for(;;)
	{
		for(i=0;i<20000;i++);
		
		// turn LEDs off
		P5OUT = 0;
		P2OUT = 0;
		
		for(i=0;i<20000;i++);
		
		// turn LEDs on
		P5OUT = LED3;
		P2OUT = LED1 | LED2;
	}
	
	return 0;
}
