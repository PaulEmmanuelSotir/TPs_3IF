#ifndef LCD_H
#define LCD_H

#define LCD_START (unsigned char*)145
#define LCD_END (unsigned char*)164


unsigned char tbNumber[10];

/*  Initialize the LCD_A controller
    
    claims P5.2-P5.4, P8, P9, and P10.0-P10.5
    assumes ACLK to be default 32khz (LFXT1)
*/
void lcd_init();

void lcd_display_number(int number);

void lcd_clear();

void lcd_fill();

#endif // LCD_H
