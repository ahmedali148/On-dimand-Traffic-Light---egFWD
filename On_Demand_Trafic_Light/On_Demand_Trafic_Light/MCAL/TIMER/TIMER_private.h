/*
 * TIMER_private.h
 *
 * Created: 06/11/2022 04:53:03 م
 *  Author: M
 */ 


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*Mode Register*/
#define SREG              (*(volatile uint8*)(0x5F))

/*General Timer Registers*/
#define TIMSK             (*(volatile uint8*)(0x59))
#define TIFR              (*(volatile uint8*)(0x58))

/*Timer0 Registers*/
#define OCR0              (*(volatile uint8*)(0x5C))
#define TCCR0             (*(volatile uint8*)(0x53))
#define TCNT0             (*(volatile uint8*)(0x52))

/*Timer1 Registers*/
#define TCCR1            (*(volatile uint16*)(0x4E))
#define TCNT1            (*(volatile uint16*)(0x4C))
#define OCR1A            (*(volatile uint16*)(0x4A))
#define OCR1B            (*(volatile uint16*)(0x48))
#define ICR1             (*(volatile uint16*)(0x56))


#endif /* TIMER_PRIVATE_H_ */