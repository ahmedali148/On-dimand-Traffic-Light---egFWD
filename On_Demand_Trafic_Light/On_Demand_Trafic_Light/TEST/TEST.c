/*
 * TEST.c
 *
 * Created: 19/11/2022 08:15:19 م
 *  Author: M
 */ 

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "../HAL/LED/LED.h"
#include "../HAL/Button/Button.h"

#include "../APP/APP.h"
#include "TEST.h"

TEST_State_t TEST_Modules(void)
{
	TEST_State_t Local_return = TEST_OK;
	if((Button_voidAttachInterrupt(B_INT_0, B_FALLING_EDGE_MODE, *Pedestrian_Mode) == Button_OK) && (APP_start()== APP_OK) && (LED_init() == LED_OK))
	{
		Local_return = TEST_OK;
	}
	else
	{
		Local_return = TEST_ERROR;
	}
	return Local_return;
}