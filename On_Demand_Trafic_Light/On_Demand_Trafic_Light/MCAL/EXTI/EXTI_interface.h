/*
 * EXTI_interface.h
 *
 * Created: 12/11/2022 01:10:17 ص
 *  Author: Ahmed Ali
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/*External interrupt numbers*/
#define INT_0    		(0)
#define INT_1    		(1)
#define INT_2           (2)

/*External interrupt modes*/
#define LOW_LEVEL_MODE      (0)
#define LOGICAL_CHANGE_MODE (1)
#define FALLING_EDGE_MODE   (2)
#define RISING_EDGE_MODE    (3)

/*This function is used to enable external interrupt [INT_0 - INT_1 - INT_2]*/
void EXTI_voidEnableInterrupt(uint8 Copy_u8interruptNumber);

/*This function is used to disable external interrupt [INT_0 - INT_1 - INT_2]*/
void EXTI_voidDisableInterrupt(uint8 Copy_u8interruptNumber);

/*This function is used to attach  a specific application function to specific ISR*/
void EXTI_voidAttachInterrupt(uint8 Copy_u8interruptNumber, uint8 Copy_u8interruptMode, void (*pfunc)(void));


#endif /* EXTI_INTERFACE_H_ */