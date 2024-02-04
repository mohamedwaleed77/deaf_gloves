
#include <util/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Cfg.h"
#include <stdlib.h>


#define F_CPU 8000000UL
#define NULL 0

void MUART_voidInit(void)
{
	u16 local_u16BaudRate = BAUD_RATE_EQUATION;

	// Set Baudrate
	UBRRL = (u8) local_u16BaudRate;
	UBRRH = (u8) (local_u16BaudRate >> 8);

	// Character Size 8-bit
	CLR_BIT(UCSRB,2);

	// Character Size 8-bit
	// Mode Asynchronous operation
	// Parity Disabled
	// 1 Stop Bit
	UCSRC = CONC_BIT(1,0,0,0,0,1,1,0);

	// Enable Receiver
	// Enable Transmitter
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);

}


void MUART_voidSendByteSyncBlocking (u8 A_u8DataByte)
{
	// wait until UDR is empty
	while(GET_BIT(UCSRA,5)==0);//0=not empty

	// Set Data into Tx Register and start Transmission
	UDR = A_u8DataByte;

	// wait until UDR is empty
	while(GET_BIT(UCSRA,5)==0);

	// Clear transmit Interrupt flag
	SET_BIT(UCSRA,6);

}

void MUART_voidSendStringSyncBlocking (u8 *A_pu8String)
{
	while (*A_pu8String > 0)
	{
		MUART_voidSendByteSyncBlocking(*A_pu8String++);
	}
}


u8 MUART_u8ReadByteSyncBlocking (void)
{
	// Wait for Rx Flag
	while (GET_BIT(UCSRA,7)==0);//0=not finished
	return UDR;
}

u8* MUART_u8ReadStringSyncBlocking(void) {
    u8* LocalStringRead = (u8 *)malloc(sizeof(u8));
    u8 LocalStringLastByte = MUART_u8ReadByteSyncBlocking();
    u8 LEN = 0;

    while (LocalStringLastByte != '\n' && LocalStringLastByte !=NULL ) {  // Change the delimiter to '\n' or another appropriate value
        LocalStringRead = (u8 *)realloc(LocalStringRead, (LEN + 1) * sizeof(u8));
        LocalStringRead[LEN] = LocalStringLastByte;
        LEN++;
        LocalStringLastByte = MUART_u8ReadByteSyncBlocking();
    }

    LocalStringRead = (u8 *)realloc(LocalStringRead, (LEN + 1) * sizeof(u8));
    if (LocalStringRead == NULL) {
        free(LocalStringRead);
        return NULL;
    }

    LocalStringRead[LEN] = '\0';
    return LocalStringRead;
    /* don't forget to free the variable that holds this function result */
}


