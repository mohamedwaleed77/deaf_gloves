/*
 * TIMERS_Private.h
 *
 *  Created on: Apr 30, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_TIMERS_TIMERS_PRIVATE_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_PRIVATE_H_

#define TCCR0 (*(volatile u8 *)0x53)
#define TCNT0 (*(volatile u8 *)0x52)
#define OCR0  (*(volatile u8 *)0x5C)
#define TIMSK (*(volatile u8 *)0x59)
#define TIFR  (*(volatile u8 *)0x58)


#define TCCR1A (*(volatile u8 *)0x4F)
#define TCCR1B (*(volatile u8 *)0x4E)
#define TCNT1H (*(volatile u8 *)0x4D)
#define TCNT1L (*(volatile u8 *)0x4C)
#define TCNT1  (*(volatile u16 *)0x4C)
#define OCR1A  (*(volatile u16 *)0x4A)
#define OCR1B  (*(volatile u8 *)0x48)
#define ICR1H  (*(volatile u8 *)0x47)
#define ICR1L  (*(volatile u8 *)0x46)
#define ICR1   (*(volatile u16 *)0x46)


#define TIMER0_CLK_MASK     0b11111000
#define TIMER0_CLK_OC0_MASK 0b11001000
#endif /* INCLUDE_MCAL_TIMERS_TIMERS_PRIVATE_H_ */
