/*
 * Button.c
 *
 * Created: 19/11/2022 05:43:33 م
 *  Author: M
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/EXTI/EXTI_interface.h"
#include "Button.h"

/*This function call Enable interrupt attach interrupt*/
Button_State_t Button_voidAttachInterrupt(uint8 Copy_u8interruptNumber, uint8 Copy_u8interruptMode, void (*pfunc)(void))
{			
		/*attach  a specific application function to  ISR0*/
		EXTI_voidAttachInterrupt(Copy_u8interruptNumber, Copy_u8interruptMode, *pfunc);
		
		/*Enable Interrupt INT_0*/
		EXTI_voidEnableInterrupt(Copy_u8interruptNumber);
		
		return Button_OK;
}