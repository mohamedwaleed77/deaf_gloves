#ifndef _LCD_CFG_

#define LCD_RS_PIN_ID                  0
#define LCD_RW_PIN_ID                  1
#define LCD_E_PIN_ID                   2
//LCD COMMANDS:
#define LCD_GO_TO_HOME                 	0x02
#define LCD_CLEAR_COMMAND              	0x01
#define LCD_BACKLIGHT					0x08
#define LCD_CGRAM_START          		0x40
#define LCD_SET_CURSOR_LOCATION  		0x80

#define slave_address_fixed_bits	0x20 << 1		//0x20 as A0=A1=A2=0
#endif
