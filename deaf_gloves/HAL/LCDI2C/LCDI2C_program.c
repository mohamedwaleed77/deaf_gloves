#include <util/delay.h>
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/I2C/TWI_interface.h"
#include "LCDI2C_Interface.h"
#include "LDCI2C_CFG.h"



u8 global_LCD=0;//performs like a buffer

static u8 PCF8574_write(u8 data)
{
	_delay_ms(1);
	data|=LCD_BACKLIGHT;//doesn't affect the data as the backlight pin is not connected to LCD
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return ERROR;

	TWI_writeByte((slave_address_fixed_bits) | WRITE);
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	TWI_writeByte(data);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
			return ERROR;

	TWI_stop();

	return SUCCESS;
}

void LCD_init(void)
{
	_delay_ms(30);
	TWI_init();
	LCD_HEART();
	LCD_sendCommand(LCD_GO_TO_HOME);//--- Return to Home
	LCD_sendCommand(0x0E);//use it for simulation only (different screen)
	LCD_sendCommand(LCD_CLEAR_COMMAND);				//--- Clear LCD


}


void LCD_sendWithHighEn(){
	SET_BIT(global_LCD,LCD_E_PIN_ID);
	PCF8574_write(global_LCD);
	_delay_ms(1);

}
void LCD_sendWithLowEn(){

		CLR_BIT(global_LCD,LCD_E_PIN_ID);
		PCF8574_write(global_LCD);
		_delay_ms(1);
}
void LCD_sendCommand(u8 command)
{
	//COMMAND MODE
	_delay_ms(1);
	CLR_BIT(global_LCD,LCD_RS_PIN_ID);
	CLR_BIT(global_LCD,LCD_RW_PIN_ID);
	LCD_sendWithHighEn();
	//high 4 bits
	global_LCD = (global_LCD & 0x0F) | (command & 0xF0);
	LCD_sendWithHighEn();
	LCD_sendWithLowEn();
	//low 4 bits
	global_LCD = (global_LCD & 0x0F) | ((command & 0x0F) << 4);
	LCD_sendWithHighEn();
	LCD_sendWithLowEn();
}


void LCD_displayCharacter(u8 data)
{//SAME as command but we set RS_PIN ->1
	_delay_ms(1);
	//DATA MODE
	SET_BIT(global_LCD,LCD_RS_PIN_ID);
	CLR_BIT(global_LCD,LCD_RW_PIN_ID);
	//high 4 bits
	global_LCD = (global_LCD & 0x0F) | (data & 0xF0);
	LCD_sendWithHighEn();
	LCD_sendWithLowEn();
	//LOW 4 bits
	global_LCD = (global_LCD & 0x0F) | ((data & 0x0F) << 4);
	LCD_sendWithHighEn();
	LCD_sendWithLowEn();
}


void LCD_displayString(const u8 *Str)
{
	u8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}

}


void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}


void LCD_HEART(void) {
    // Custom character data for heart shape
    const u8 heartCharMap[8] = {
        0b00000,
        0b01010,
        0b11111,
        0b11111,
        0b01110,
        0b00100,
        0b00000,
		0b00000
    };

    LCD_sendCommand(LCD_CGRAM_START);

    // Load the custom character data into CGRAM
    for (u8 i = 0; i < 8; ++i) {
        LCD_displayCharacter(heartCharMap[i]);
    }
}

