/*
 * LED.h
 *
 * Created: 12/11/2022 02:07:10 ص
 *  Author: M
 */ 


#ifndef LED_H_
#define LED_H_

/*LEDS Of Car PORT*/
#define LED_CAR_PORT			(0)

/*LEDS Of Car PIN*/
#define CAR_RED_LED					(0b00000001)
#define CAR_YEL_LED					(0b00000010)
#define CAR_GRN_LED					(0b00000100)


/*LEDS Of pedestrian PORT*/
#define LED_PEDESTRIAN_PORT		(2)

/*LEDS Of pedestrian PIN*/
#define PED_RED_LED					(0b00000001)
#define PED_YEL_LED					(0b00000010)
#define PED_GRN_LED					(0b00000100)

/*LEDs Status*/
#define LED_ON             (1)
#define LED_OFF            (0)

/*Timer channels*/
#define L_CHANNEL_0      (0) 
#define L_CHANNEL_1      (1)
#define L_CHANNEL_2      (2)

typedef enum
{
	LED_OK, LED_ERROR
}LED_State_t;

LED_State_t LED_init(void);

LED_State_t LED_voidTurn(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Status);
LED_State_t LED_voidBlink(uint8 Copy_u8Port, uint8 Copy_u8Pin);
LED_State_t LED_voidDelay(uint8 Copy_u8Channel, uint32 Copy_u8DelayPeriodMs);
LED_State_t LED_voidStartTimer(uint8 Copy_u8Channel);
LED_State_t LED_voidDoubleBlink(uint8 Copy_u8Port, uint8 Copy2_u8Port, uint8 Copy_u8Pin);

#endif /* LED_H_ */