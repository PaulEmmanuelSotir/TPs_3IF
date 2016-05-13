#include "msp430fg4618.h"
#include "lcd.h"

#define TACTL_TACLK			0b0000000000000000
#define TACTL_ACLK			0b0000000100000000
#define TACTL_SMCLK			0b0000001000000000
#define TACTL_INCLK			0b0000001100000000

#define TACTL_IDX1			0b0000000000000000
#define TACTL_IDX2			0b0000000001000000
#define TACTL_IDX4			0b0000000010000000
#define TACTL_IDX8			0b0000000011000000

#define TACTL_STOP			0b0000000000000000
#define TACTL_UP			0b0000000000010000
#define TACTL_CONT			0b0000000000100000
#define TACTL_UP_DOWN		0b0000000000110000

#define TACCTLx_NO_CAPTURE	0b0000000000000000
#define TACCTLx_RISING		0b0100000000000000
#define TACCTLx_FALLING		0b1000000000000000
#define TACCTLx_BOTH		0b1100000000000000

#define TACCTLx_CCIxA		0b0000000000000000
#define TACCTLx_CCIxB		0b0001000000000000
#define TACCTLx_GND			0b0010000000000000
#define TACCTLx_VCC			0b0011000000000000

#define TACCTLx_CAPT		0b0000000100000000
#define TACCTLx_COMP		0b0000000000000000

#define TASSEL_MASK			0b0000001100000000
#define IDx_MASK			0b0000000011000000
#define MCx_MASK			0b0000000000110000
#define TACLR_MASK			0b0000000000000100
#define TAIE_MASK			0b0000000000000010
#define TAIFG_MASK			0b0000000000000001

#define CCIE_MASK			0b0000000000010000

#define SMCLK_10MS 10486
#define ACLK_10MS 328

static unsigned int cpt = 0;

static void init_timer()
{
	TA0R = 0;
	CCR0 = SMCLK_10MS;
	CCTL0 = TACCTLx_RISING | TACCTLx_COMP | CCIE;
	TACTL =  TASSEL_2 | ID_0 | MC_1;
}

void mon_traitement_interuption_timer(void) {
		cpt++;
		lcd_display_number(cpt);
		P5OUT = P5OUT ^ 0x02 ; // toggle P5.1 (LED4)
		//TACTL =  TASSEL_2 | ID_0 | MC_2 | TAIE;
}

int main()
{
	lcd_init(); // Initialize screen
	P5DIR |= 0x02 ; // Set P5.1 to output direction
	
	init_timer();

	lcd_display_number(cpt);
	
	//SR |= GIE;
	
	__asm("EINT");
	
	for(;;)
	{
		
	}

	return 0;
}

int main_2()
{
	lcd_init(); // Initialize screen
	P5DIR |= 0x02 ; // Set P5.1 to output direction
	
	init_timer();

	unsigned int cpt = 0;
	lcd_display_number(cpt);
	
	for(;;)
	{
		if((TACTL & TAIFG) != 0x00)
		{
			cpt++;
			lcd_display_number(cpt);
			P5OUT = P5OUT ^ 0x02 ; // toggle P5.1 (LED4)
			
			TACTL =  TASSEL_2 | ID_1 | MC_2 | TAIE;
		}
	}

	return 0;
}

