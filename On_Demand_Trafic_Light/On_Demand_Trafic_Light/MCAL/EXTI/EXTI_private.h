/*
 * EXTI_private.h
 *
 * Created: 12/11/2022 01:10:35 ص
 *  Author: M
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define M_XTI_SREG             (*(volatile uint8*)(0x5F))
#define MEXTI_GICR             (*(volatile uint8*)(0x5B))
#define MEXTI_GIFR             (*(volatile uint8*)(0x5A))
#define MEXTI_MCUCR            (*(volatile uint8*)(0x55))
#define MEXTI_MCUCSR           (*(volatile uint8*)(0x54))



#endif /* EXTI_PRIVATE_H_ */