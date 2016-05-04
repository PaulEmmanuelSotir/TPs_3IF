#ifndef LCD_H
#define LCD_H

	void lcd_init();
	void lcd_clear();
	void lcd_fill();
	void lcd_display_digit(int pos, int digit);
	void lcd_display_number(unsigned int number);

#endif
