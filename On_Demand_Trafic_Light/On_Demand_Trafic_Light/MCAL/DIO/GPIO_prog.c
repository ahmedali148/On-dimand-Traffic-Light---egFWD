/*
 * GPIO_prog.c
 *
 * Created: 30/10/2022 02:29:32 AM
 *  Author: Ahmed Ali
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
/*This function is responsible for specific status [OUTPUT- INPUT_FLOATING -INPUT_PULLUP] to a specific port pin */
void GPIO_voidSetPinStatus(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Status)
{
    switch(Copy_u8Status)	
	{
		case GPIO_OUTPUT:
		 switch(Copy_u8Port)
		 {
			 case PORTA: GPIO_DDRA |= Copy_u8Pin; break;
			 case PORTB: GPIO_DDRB |= Copy_u8Pin; break;
			 case PORTC: GPIO_DDRC |= Copy_u8Pin; break;
			 case PORTD: GPIO_DDRD |= Copy_u8Pin; break;
			 default:/*do nothing*/               break;
		 }
		 break;
		 
		case GPIO_INPUT_FLOATING:
		 switch(Copy_u8Port)
		 {
			 case PORTA: GPIO_DDRA &= ~Copy_u8Pin; break;
			 case PORTB: GPIO_DDRB &= ~Copy_u8Pin; break;
			 case PORTC: GPIO_DDRC &= ~Copy_u8Pin; break;
			 case PORTD: GPIO_DDRD &= ~Copy_u8Pin; break;
			 default:/*do nothing*/                break;
		 }
		 break;
		 
	   case GPIO_INPUT_PULLUP:
		 switch(Copy_u8Port)
		 {
			 case PORTA: GPIO_DDRA &= ~Copy_u8Pin;
			             GPIO_PORTA |= Copy_u8Pin; break;
						 
			 case PORTB: GPIO_DDRB &= ~Copy_u8Pin;
			             GPIO_PORTB |= Copy_u8Pin; break;
						 
			 case PORTC: GPIO_DDRC &= ~Copy_u8Pin; 
			             GPIO_PORTC |= Copy_u8Pin; break;
						 
			 case PORTD: GPIO_DDRD &= ~Copy_u8Pin; 
			             GPIO_PORTD |= Copy_u8Pin; break;
						 
			 default:/*do nothing*/                 break;
		 }
		 break;
		 
		default: /*do nothing*/                     break;
		
	}
}
/*This function is responsible for specific value [HIGH -LOW] to a specific port pin*/
void GPIO_voidSetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value)
{
	   if(Copy_u8Value == GPIO_HIGH)
	   {
		   switch(Copy_u8Port)
		   
		   {
			   case PORTA: GPIO_PORTA |= Copy_u8Pin; break;
			   case PORTB: GPIO_PORTB |= Copy_u8Pin; break;
			   case PORTC: GPIO_PORTC |= Copy_u8Pin; break;
			   case PORTD: GPIO_PORTD |= Copy_u8Pin; break;
			   default:/*do nothing*/                break;
		   }
	   }
	   else
	   {
		  switch(Copy_u8Port)
		   {
			   case PORTA: GPIO_PORTA &= ~Copy_u8Pin; break;
			   case PORTB: GPIO_PORTB &= ~Copy_u8Pin; break;
			   case PORTC: GPIO_PORTC &= ~Copy_u8Pin; break;
			   case PORTD: GPIO_PORTD &= ~Copy_u8Pin; break;
			   default:/*do nothing*/                 break;
		   }   
	   }	
}
/*This function is responsible for specific port pin value [HIGH - LOW]*/
uint8 GPIO_u8GetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
	     uint8 Copy_Pu8Value = 0;
		switch(Copy_u8Port)
		{
			case PORTA: Copy_Pu8Value = GET_BIT(GPIO_PORTA, Copy_u8Pin); break;
			case PORTB: Copy_Pu8Value = GET_BIT(GPIO_PORTB, Copy_u8Pin); break;
			case PORTC: Copy_Pu8Value = GET_BIT(GPIO_PORTC, Copy_u8Pin); break;
			case PORTD: Copy_Pu8Value = GET_BIT(GPIO_PORTD, Copy_u8Pin); break;
		}
	return Copy_Pu8Value;
}
/*This function is responsible for toggling specific port pin [HIGH->LOW -LOW->HIGH] */
void GPIO_voidTogglePinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
		switch(Copy_u8Port)
		{
			case PORTA: GPIO_PORTA ^= Copy_u8Pin; break;
			case PORTB: GPIO_PORTB ^= Copy_u8Pin; break;
			case PORTC: GPIO_PORTC ^= Copy_u8Pin; break;
			case PORTD: GPIO_PORTD ^= Copy_u8Pin; break;
			default:/*do nothing*/                      break;
		}
}