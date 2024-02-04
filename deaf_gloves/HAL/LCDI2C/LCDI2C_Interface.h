#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/STD_TYPES.h"



#define ERROR 							0
#define SUCCESS 						1



//read an write for i2c
#define	WRITE							0
#define READ							1

static u8 PCF8574_write(u8 data);
void LCD_init(void);
void LCD_sendWithHighEn();
void LCD_sendWithLowEn();
void LCD_sendCommand(u8 command);
void LCD_displayCharacter(u8 data);
void LCD_displayString(const u8 *Str);
void LCD_clearScreen(void);
void LCD_Heart(void);

#endif /* LCD_H_ */
