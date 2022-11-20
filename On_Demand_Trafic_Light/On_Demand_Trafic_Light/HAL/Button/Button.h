/*
 * Button.h
 *
 * Created: 19/11/2022 05:43:17 م
 *  Author: M
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

/*External interrupt numbers*/
#define B_INT_0  (0)
#define B_INT_1  (1)
#define B_INT_2  (2)

/*External interrupt modes*/
#define B_LOW_LEVEL_MODE       (0)
#define B_LOGICAL_CHANGE_MODE  (1)
#define B_FALLING_EDGE_MODE    (2)
#define B_RISING_EDGE_MODE     (3) 

typedef enum
{
	Button_OK, Button_ERROR
}Button_State_t;

Button_State_t Button_voidAttachInterrupt(uint8 Copy_u8interruptNumber, uint8 Copy_u8interruptMode, void (*pfunc)(void));




#endif /* BUTTON_H_ */