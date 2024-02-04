/*
 * TIMERS_Interface.h
 *
 *  Created on: Apr 30, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_

#define NORMAL_MODE			0
#define PHASE_CORRECT_MODE	1
#define CTC_MODE			2
#define FAST_PWM_MODE		3

typedef enum{
	micro=0,
	milli,
	second,
}time_unit;


void MTIMER0_voidInit (void);
void MTIMER0_voidSetCTCCallback (void (*A_PtrToFunc)(void));

#endif /* INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_ */
