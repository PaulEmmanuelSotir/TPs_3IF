#include "lcd.h"

int sum_eight(int a, int b, int c, int d, int e, int f, int g, int h)
{
	int x= a + b + c + d + e + f + g + h;
	return x;
}
int main(void)
{
	volatile int x=0;
	lcd_init();
	x=sum_eight(100,200,300,400,500,600,700,800);
	lcd_display_number(x);
	for(;;);
	return 0;
}
