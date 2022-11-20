/*
 * LED.c
 *
 * Created: 12/11/2022 02:06:44 AM
 *  Author: Ahmed Ali
 */ 


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/GPIO_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"
#include "LED.h"

LED_State_t LED_init(void)
{
    TIMER_voidInitDelay(CHANNEL_0);
	GPIO_voidSetPinStatus(PORTD, PIN2, GPIO_INPUT_PULLUP);
	GPIO_voidSetPinStatus(LED_CAR_PORT, CAR_RED_LED|CAR_GRN_LED|CAR_YEL_LED, GPIO_OUTPUT);
	GPIO_voidSetPinStatus(LED_PEDESTRIAN_PORT, PED_RED_LED|PED_GRN_LED|PED_YEL_LED, GPIO_OUTPUT);
	return LED_OK;
}


LED_State_t LED_voidTurn(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Status)
{
	GPIO_voidSetPinValue(Copy_u8Port, Copy_u8Pin, Copy_u8Status);
	return LED_OK;
}

LED_State_t LED_voidBlink(uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
	/*Car's YELLOW LED Blink*/
	for(uint32 i = 0;i <5000;i+=500)
	{
		GPIO_voidTogglePinValue(Copy_u8Port,Copy_u8Pin);
		//Global_Copy_u8StateFlag = 1;
		TIMER_voidDelayMs_Sync(CHANNEL_0,500);
	}
	return LED_OK;
}

LED_State_t LED_voidDoubleBlink(uint8 Copy_u8Port, uint8 Copy2_u8Port, uint8 Copy_u8Pin)
{
	/*Car's YELLOW LED Blink*/
	for(uint32 i = 0;i <5000;i+=500)
	{
		GPIO_voidTogglePinValue(Copy_u8Port,Copy_u8Pin);
		GPIO_voidTogglePinValue(Copy2_u8Port,Copy_u8Pin);
		//Global_Copy_u8StateFlag = 1;
		TIMER_voidDelayMs_Sync(CHANNEL_0,500);
	}
	return LED_OK;
}

LED_State_t LED_voidDelay(uint8 Copy_u8Channel, uint32 Copy_u8DelayPeriodMs)
{
	TIMER_voidDelayMs_Sync(Copy_u8Channel, Copy_u8DelayPeriodMs);
	return LED_OK;
}

LED_State_t LED_voidStartTimer(uint8 Copy_u8Channel)
{
	TIMER_voidStartTimer(CHANNEL_0);
	return LED_OK;
}
