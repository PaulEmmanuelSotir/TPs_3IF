
#include <msp430fg4618.h>

#define LED1 BIT2
#define LED2 BIT1
#define LED3 BIT1

#define SW1 BIT0
#define SW2 BIT1

volatile unsigned int i;

int main(void)
{
	// set P5.1 to output direction
	P5DIR = LED3;
	
	P2DIR = P2DIR | (LED1 | LED2);
	P1DIR = P1DIR & !SW1;

	
	for(;;)
	{
		
		/* turn all LEDS off */
		P5OUT &= !LED3;
		P2OUT &= !(LED1 | LED2);
		
		while ((P1IN & SW1) != 0x00);
		while ((P1IN & SW1) == 0x00);
		
		P5OUT &= !LED3;
		P2OUT &= !LED2;
		P2OUT |= LED1;
		
		while ((P1IN & SW1) != 0x00);
		while ((P1IN & SW1) == 0x00);
		
		P5OUT &= !LED3;
		P2OUT &= !LED1;
		P2OUT |= LED2;
		
		while ((P1IN & SW1) != 0x00);
		while ((P1IN & SW1) == 0x00);
		
		P2OUT &= !(LED1 | LED2);
		P5OUT |= LED3;
		
		while ((P1IN & SW1) != 0x00);
		while ((P1IN & SW1) == 0x00);
	}
	
	return 0;
}
