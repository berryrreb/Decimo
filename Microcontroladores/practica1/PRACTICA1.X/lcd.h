/* 
 * File:   lcd.h
 * Author: Emiliano
 *
 * Created on October 26, 2020, 9:13 AM
 */
#ifndef HD44780_H
#define HD44780_H

//==============================================================================
// Lcd Connection.
// Set in  digital mode these pins in your code.
// Pin RW connect to GND.
//==============================================================================
#define LCD_RD7 PORTDbits.RD0 // D7
#define TRISRD7 TRISDbits.TRISD0

#define LCD_RD6 PORTDbits.RD1 // D6
#define TRISRD6 TRISDbits.TRISD1

#define LCD_RD5 PORTDbits.RD2 // D5
#define TRISRD5 TRISDbits.TRISD2

#define LCD_RD4 PORTDbits.RD3 // D4
#define TRISRD4 TRISDbits.TRISD3

#define LCD_EN PORTDbits.RD4 // EN
#define TRISEN TRISDbits.TRISD4

#define LCD_RS PORTDbits.RD5 // RS
#define TRISRS TRISDbits.TRISD5

//==============================================================================
// Available Lcd Commands.
//==============================================================================
#define LCD_FIRST_ROW 128
#define LCD_SECOND_ROW 192
#define LCD_THIRD_ROW 148
#define LCD_FOURTH_ROW 212
#define LCD_CLEAR 1
#define LCD_RETURN_HOME 2
#define LCD_CURSOR_OFF 12
#define LCD_UNDERLINE_ON 14
#define LCD_BLINK_CURSOR_ON 15
#define LCD_MOVE_CURSOR_LEFT 16
#define LCD_MOVE_CURSOR_RIGHT 20
#define LCD_TURN_OFF 0
#define LCD_TURN_ON 8
#define LCD_SHIFT_LEFT 24
#define LCD_SHIFT_RIGHT 28

//==============================================================================
// Function Prototypes.
//==============================================================================
void Lcd_Init(void);
void Lcd_ConstText(unsigned char y, unsigned char x, const char *buffer);
//void Lcd_Text(unsigned char y, unsigned char x, char *buffer);
void Lcd_WriteChar(unsigned char y, unsigned char x, char c);
void Lcd_CharCP(char c);
void Lcd_Command(unsigned char command);

#endif /* HD44780_H */
