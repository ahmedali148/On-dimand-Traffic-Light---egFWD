/*
 * EXTI_prog.c
 *
 * Created: 12/11/2022 01:11:36 ص
 *  Author: M
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "avr/interrupt.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"


/*Global pointer used to carry application function address to ISR_INT_0*/
void (*Globalfunc_INT_0)(void) = NULL;

/*Global pointer used to carry application function address to ISR_INT_1*/
void (*Globalfunc_INT_1)(void) = NULL;

/*Global pointer used to carry application function address to ISR_INT_2*/
void (*Globalfunc_INT_2)(void) = NULL;

/*This function is used to enable external interrupt [INT_0 - INT_1 - INT_2]*/
void EXTI_voidEnableInterrupt(uint8_t Copy_u8interruptNumber)
{
		/*Enable global interrupts*/
		SET_BIT(SREG, 7);

		/*Switching over interrupt number*/
		switch(Copy_u8interruptNumber)
		{
			case INT_0: SET_BIT(MEXTI_GICR, 6); /*Enable INT_0*/
			           break;

			case INT_1: SET_BIT(MEXTI_GICR, 7); /*Enable INT_1*/
                       break;

			case INT_2: SET_BIT(MEXTI_GICR, 5); /*Enable INT_2*/
			           break;

			default: /*Do nothing*/
			           break;
		}
}

/*This function is used to disable external interrupt [INT_0 - INT_1 - INT_2]*/
void EXTI_voidDisableInterrupt(uint8_t Copy_u8interruptNumber)
{
			/*Switching over interrupt number*/
			switch(Copy_u8interruptNumber)
			{
				case INT_0: CLR_BIT(MEXTI_GICR, 6); /*Enable INT_0*/
				break;

				case INT_1: CLR_BIT(MEXTI_GICR, 7); /*Enable INT_1*/
				break;

				case INT_2: CLR_BIT(MEXTI_GICR, 5); /*Enable INT_2*/
				break;

				default: /*Do nothing*/
				break;
			}
}

/*This function is used to attach  a specific application function to specific ISR*/
void EXTI_voidAttachInterrupt(uint8 Copy_u8interruptNumber, uint8_t Copy_u8interruptMode, void (*pfunc)(void))
{
	/*Switching over interrupt number*/
	switch(Copy_u8interruptNumber)
	{
		case INT_0:

		/*Setting the application function address for callback*/
		Globalfunc_INT_0 = pfunc;

		MEXTI_MCUCR &= 0xFC;                   /*Clearing bit0 and bit1*/
      
	    MEXTI_MCUCR |= (Copy_u8interruptMode); /*Setting the INT_0 mode*/ 
		
		break;

		case INT_1:

		/*Setting the application function address for callback*/
		Globalfunc_INT_1 = pfunc;

		MEXTI_MCUCR &= 0xF3;                      /*Clearing bit2 and bit3*/

		MEXTI_MCUCR |= (Copy_u8interruptMode << 2);  /*Setting the INT_1 mode*/
		
		break;

		/*In case of interrupt 2*/
		case INT_2:

		/*Setting the application function address for callback*/
		Globalfunc_INT_2 = pfunc;

		/*Switching over interrupt modes*/
		switch(Copy_u8interruptMode)
		{
			/*In case of falling edge mode*/
			case FALLING_EDGE_MODE:

			/*Enable falling edge mode for INT_2*/
			CLR_BIT(MEXTI_MCUCSR, 6);        break;

			/*In case of falling edge mode*/
			case RISING_EDGE_MODE:

			/*Enable rising edge mode for INT_2*/
			SET_BIT(MEXTI_MCUCSR, 6);       break;

			default: /*Do nothing*/         break;

		}

		break;

		default:  /*Do nothing*/         break;
	}
}

/*INT_0 ISR*/
ISR(INT0_vect)
{
	
	/*Checking if the global pointer to function is NULL or not*/
	if(Globalfunc_INT_0 != NULL)
	{
		/*Calling application function*/
		Globalfunc_INT_0();
	}
	else
	{
		/*Do nothing*/
	}
}

/*INT_1 ISR*/
ISR(INT1_vect)
{
	/*Checking if the global pointer to function is NULL or not*/
	if(Globalfunc_INT_1 != NULL)
	{
		/*Calling application function*/
		Globalfunc_INT_1();
	}
	else
	{
		/*Do nothing*/
	}
}

/*INT_2 ISR*/
ISR(INT2_vect)
{
	/*Checking if the global pointer to function is NULL or not*/
	if(Globalfunc_INT_2 != NULL)
	{
		/*Calling application function*/
		Globalfunc_INT_2();
	}
	else
	{
		/*Do nothing*/
	}
}
