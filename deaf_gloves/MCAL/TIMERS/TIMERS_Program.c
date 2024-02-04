/*
 * TIMERS_Program.c
 *
 *  Created on: Apr 30, 2023
 *      Author: abdelrahmanhossam
 */

/****************************************************/
/* Library Directives							    */
/****************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/****************************************************/
/* TIMERS Directives		     					*/
/****************************************************/
#include "TIMERS_Interface.h"
#include "TIMERS_Private.h"
#include "TIMERS_Cfg.h"

#define NULL 0

void (*TIMER0_CTC_CALLBACK)(void) = NULL;



void MTIMER0_voidInit (void)
{
	// CTC Mode
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);

	// Enable CTC Interrupt
	SET_BIT(TIMSK,1);
	CLR_BIT(TIMSK,0);

	// Set OCR0 Value
	OCR0 = OCR0_VALUE;

	// Start Timer by setting its clock
	TCCR0 &= 0b11001000;
	TCCR0 |= (TIMER0_CLK | (CTC_OC0_MODE <<4));

}

void MTIMER0_voidSetCTCCallback (void (*A_PtrToFunc)(void))
{
	if (A_PtrToFunc != NULL)
	{
		TIMER0_CTC_CALLBACK = A_PtrToFunc;
	}
}


void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if (TIMER0_CTC_CALLBACK != NULL)
	{
		TIMER0_CTC_CALLBACK();
	}
}










