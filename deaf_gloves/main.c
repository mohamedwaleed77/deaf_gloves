
#include <util/delay.h>
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/TEXT_TRANSLATOR.h"
#include "HAL/FLEX_SENSOR/FLEX_SENSOR_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "HAL/LCDI2C/LCDI2C_Interface.h"
#include "MCAL/TIMERS/TIMERS_Interface.h"
#include "MCAL/GI/GI_interface.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#define fixed_resistor 100000
#define Vin 5000

#define F_CPU 8000000UL
#define ISBEND(value, threshold) ((value) > (threshold) ? 1 : 0)
#define ISEQUAL(value, value2) ((value) == (value2) ? 1 : 0)
#define TO_BINARY(b1, b2, b3, b4, b5) \
    (((b1) << 4) | ((b2) << 3) | ((b3) << 2) | ((b4) << 1) | (b5))

struct DictionaryEntry dictionary[] = {
    {0b00000, "PROJECT"},
    {0b00001, "banana"},
    {0b00010, "orange"},
    {0b00011, "grape"},
    {0b00100, "kiwi"},
    {0b00101, "pear"},
    {0b00110, "melon"},
    {0b00111, "cherry"},
    {0b01000, "You"},
    {0b01001, "lime"},
    {0b01010, "blueberry"},
    {0b01011, "strawberry"},
    {0b01100, "raspberry"},
    {0b01101, "blackberry"},
    {0b01110, "pineapple"},
    {0b01111, "mango"},
    {0b10000, "watermelon"},
    {0b10001, "peach"},
    {0b10010, "plum"},
    {0b10011, "apricot"},
    {0b10100, "nectarine"},
    {0b10101, "fig"},
    {0b10110, "pomegranate"},
    {0b10111, "coconut"},
    {0b11000, "kiwi"},
    {0b11001, "grapefruit"},
    {0b11010, "papaya"},
    {0b11011, "avocado"},
    {0b11100, "cantaloupe"},
    {0b11101, "honeydew"},
    {0b11110, "dragonfruit"},
    {0b11111, "passionfruit"},
};

u8 GET_STATS();
void Timer0_CTC();
u16 local_u16DigitalValue, local_u16AnalogValue;
u8 hand_analog_reads[5];
u8 pre_stats=0,stats=0;


int main (void)
{
	MDIO_voidInit();
	MADC_voidInit();
	MGI_voidEnable();
	LCD_init();
	LCD_displayString("I ");
	LCD_displayCharacter(0);
	LCD_displayString(" IMT");
	_delay_ms(10000);
	MTIMER0_voidSetCTCCallback(Timer0_CTC);
	MTIMER0_voidInit();
	MUART_voidInit();
	while(1)
	{

	}
}


u8 GET_STATS(){
	// Read in mv
	for (u8 i=0;i<5;i++){
		local_u16DigitalValue = MADC_u16GetDigitalvalue(i);
		local_u16AnalogValue  = (local_u16DigitalValue * 5000UL) / 1024;
		hand_analog_reads[i]=HFLEX_SENSOR_CALCULATE_RES(local_u16AnalogValue,Vin,fixed_resistor)/1000;

	}
	stats = TO_BINARY(
	    ISBEND(hand_analog_reads[0], 25),
	    ISBEND(hand_analog_reads[1], 25),
	    ISBEND(hand_analog_reads[2], 25),
	    ISBEND(hand_analog_reads[3], 25),
	    ISBEND(hand_analog_reads[4], 25)
		);
	return stats;
}


void Timer0_CTC() {
    static u16 counter = 0;
    counter++;
    u8 text, command_verified = 0;
    u8 *receiver;

    if (counter == 5000) {//10000=2 seconds
        counter = 0;
        stats = GET_STATS();

        switch (ISEQUAL(stats, pre_stats)) {
            case 1:
                // Do nothing as no changes occurred
                break;
            case 0:
                text = lookupWord(stats, dictionary, 32);
                LCD_clearScreen();
                MUART_voidSendStringSyncBlocking(text);
                receiver = MUART_u8ReadStringSyncBlocking();

                if (receiver) {
                            LCD_displayString(receiver);

                }
                else {
                    LCD_displayString("Error");
                }

                free(receiver);
                pre_stats = stats;
                break;
        }
    }
}

