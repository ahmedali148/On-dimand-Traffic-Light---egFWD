/*
 * GPIO_interface.h
 *
 * Created: 30/10/2022 02:29:15 ص
 *  Author: M
 */ 


#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#define GPIO_LOW       (0)
#define GPIO_HIGH      (1)

//GPIO Ports
#define PORTA     (0)
#define PORTB     (1)
#define PORTC     (2)
#define PORTD     (3)

//GPIO Pins
#define PIN0      (0b00000001)
#define PIN1      (0b00000010)
#define PIN2      (0b00000100)
#define PIN3      (0b00001000)
#define PIN4      (0b00010000)
#define PIN5      (0b00100000)
#define PIN6      (0b01000000)
#define PIN7      (0b10000000)

//GPIO Status
#define GPIO_OUTPUT             (0)
#define GPIO_INPUT_PULLUP       (1)
#define GPIO_INPUT_FLOATING     (2)


void GPIO_voidSetPinStatus(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Status);
void GPIO_voidSetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value);
uint8 GPIO_u8GetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin);
void GPIO_voidTogglePinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin);


#endif /* GPIO_INTERFACE_H_ */