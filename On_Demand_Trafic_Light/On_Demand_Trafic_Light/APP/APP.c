/*
 * APP.c
 *
 * Created: 12/11/2022 04:29:57 ص
 *  Author: M
 */ 

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "../HAL/LED/LED.h"
#include "../HAL/Button/Button.h"

#include "APP.h"

/*Global Flag To Know The Car LED State*/
uint8 Global_Copy_u8StateFlag;

extern  Global_u32timers_remainingTime;



void Pedestrian_Mode(void)
{
	/*if pressed when the cars' Red LED is on*/
	if(Global_Copy_u8StateFlag == 0)
	{
		/* the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds*/
		LED_voidTurn(LED_CAR_PORT, CAR_RED_LED, LED_ON);
		LED_voidTurn(LED_PEDESTRIAN_PORT, PED_GRN_LED, LED_ON);
		LED_voidDelay(L_CHANNEL_0, 5000);
		LED_voidTurn(LED_CAR_PORT, CAR_RED_LED, LED_OFF);
		LED_voidTurn(LED_PEDESTRIAN_PORT, PED_GRN_LED, LED_OFF);
	}
	
	/*if pressed when the cars' Green LED is on or the cars' Yellow LED is blinking*/
	else if(Global_Copy_u8StateFlag==1||Global_Copy_u8StateFlag==2)
	{
		LED_voidTurn(LED_PEDESTRIAN_PORT,PED_RED_LED, LED_ON);
		LED_voidTurn(LED_CAR_PORT,CAR_GRN_LED, LED_ON);
		LED_voidDelay(L_CHANNEL_0,Global_u32timers_remainingTime);
		LED_voidTurn(LED_PEDESTRIAN_PORT,PED_RED_LED, LED_OFF);
		LED_voidTurn(LED_CAR_PORT,CAR_GRN_LED, LED_OFF);		
		
		LED_voidDoubleBlink(LED_CAR_PORT, LED_PEDESTRIAN_PORT, CAR_YEL_LED);
		//LED_voidBlink(LED_CAR_PORT | LED_PEDESTRIAN_PORT , CAR_YEL_LED |PED_YEL_LED);

		LED_voidTurn(LED_CAR_PORT,CAR_YEL_LED, LED_OFF);
		LED_voidTurn(LED_PEDESTRIAN_PORT,PED_YEL_LED, LED_OFF);
		LED_voidTurn(LED_PEDESTRIAN_PORT,PED_GRN_LED, LED_ON);
		LED_voidTurn(LED_CAR_PORT,CAR_RED_LED, LED_ON);
		LED_voidDelay(L_CHANNEL_0, 5000);
		LED_voidTurn(LED_PEDESTRIAN_PORT,PED_GRN_LED, LED_OFF);
		LED_voidTurn(LED_CAR_PORT,CAR_RED_LED, LED_OFF);
		
		LED_voidDoubleBlink(LED_CAR_PORT, LED_PEDESTRIAN_PORT, CAR_YEL_LED);
       //LED_voidBlink(LED_CAR_PORT | LED_PEDESTRIAN_PORT , CAR_YEL_LED |PED_YEL_LED);				
	}
	
	LED_voidTurn(LED_CAR_PORT,CAR_YEL_LED, LED_OFF);
	LED_voidTurn(LED_PEDESTRIAN_PORT,PED_YEL_LED, LED_OFF);	
	
	LED_voidTurn(LED_CAR_PORT,CAR_GRN_LED, LED_ON);
	LED_voidTurn(LED_PEDESTRIAN_PORT, PED_RED_LED, LED_ON);
	LED_voidDelay(L_CHANNEL_0, 5000);
	LED_voidTurn(LED_CAR_PORT,CAR_GRN_LED, LED_OFF);
	LED_voidTurn(LED_PEDESTRIAN_PORT, PED_RED_LED, LED_OFF);
	LED_voidStartTimer(L_CHANNEL_0);	
}

APP_State_t APP_start(void)
{
	if(LED_init()== LED_OK)
	{
/*____________________*pedestrian mode______________________*/
      
	    Button_voidAttachInterrupt(B_INT_0, B_FALLING_EDGE_MODE, *Pedestrian_Mode);
	
/*_____________________*Normal Mode_________________________*/	
		
		/*Car's RED LED turn ON*/
		LED_voidTurn(LED_CAR_PORT, CAR_RED_LED, LED_ON);
		Global_Copy_u8StateFlag = 0;
		
		/*Delay 5 sec*/
		LED_voidDelay(L_CHANNEL_0, 5000);
		
		/*Car's RED LED turn OFF*/
		LED_voidTurn(LED_CAR_PORT, CAR_RED_LED, LED_OFF);
		
		/*Car's YELLOW LED Blink*/
		LED_voidBlink(LED_CAR_PORT,CAR_YEL_LED);
		Global_Copy_u8StateFlag = 1;

		/*Car's YELLOW LED turn OFF*/
		LED_voidTurn(LED_CAR_PORT, CAR_YEL_LED, LED_OFF);
		
		/*Car's GREEN LED turn ON*/
		LED_voidTurn(LED_CAR_PORT, CAR_GRN_LED, LED_ON);
		Global_Copy_u8StateFlag = 2;
		
		/*Delay 5 sec*/
		LED_voidDelay(L_CHANNEL_0, 5000);
		
		/*Car's GREEN LED turn OFF*/
		LED_voidTurn(LED_CAR_PORT, CAR_GRN_LED, LED_OFF);
		
		/*Car's YELLOW LED Blink*/
		LED_voidBlink(LED_CAR_PORT,CAR_YEL_LED);
		Global_Copy_u8StateFlag = 1;
		
		/*Car's YELLOW LED turn OFF*/
		LED_voidTurn(LED_CAR_PORT, CAR_YEL_LED, LED_OFF);
	}
	return APP_OK;	
}