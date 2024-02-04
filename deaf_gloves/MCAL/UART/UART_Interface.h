
#ifndef INCLUDE_MCAL_UART_UART_INTERFACE_H_
#define INCLUDE_MCAL_UART_UART_INTERFACE_H_

typedef enum{
	UART_RX_INTERRUPT = 0,
	UART_UDRE_INTERRUPT ,
	UART_TX_INTERRUPT
}UART_INTERRUPTS_e;

void MUART_voidInit(void);
void MUART_voidSendByteSyncBlocking (u8 A_u8DataByte);
u8 MUART_u8ReadByteSyncBlocking (void);
u8* MUART_u8ReadStringSyncBlocking (void);
void MUART_voidSendStringSyncBlocking (u8 *A_pu8String);
#endif /* INCLUDE_MCAL_UART_UART_INTERFACE_H_ */
