/*
 * GPIO_private.h
 *
 * Created: 30/10/2022 02:28:46 AM
 *  Author: M
 */ 


#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

//PORTA registers
#define GPIO_PORTA       (*(volatile uint8*)(0x3B))
#define GPIO_DDRA        (*(volatile uint8*)(0x3A))
#define GPIO_PINA        (*(volatile uint8*)(0x39))

//PORTB registers
#define GPIO_PORTB 		 (*(volatile uint8*)(0x38))
#define GPIO_DDRB        (*(volatile uint8*)(0x37))
#define MGPIO_PINC       (*(volatile uint8*)(0x36))

//PORTC registers
#define GPIO_PORTC 		(*(volatile uint8*)(0x35))
#define GPIO_DDRC       (*(volatile uint8*)(0x34))
#define GPIO_PINC       (*(volatile uint8*)(0x33))

//PORTD registers
#define GPIO_PORTD 		 (*(volatile uint8*)(0x32))
#define GPIO_DDRD        (*(volatile uint8*)(0x31))
#define GPIO_PIND        (*(volatile uint8*)(0x30))


#endif /* GPIO_PRIVATE_H_ */