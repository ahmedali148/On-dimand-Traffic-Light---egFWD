/*
 * TIMER_interface.h
 *
 * Created: 06/11/2022 04:52:36 م
 *  Author: M
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


/*Timer channels*/
#define CHANNEL_0      (0)
#define CHANNEL_1      (1)
#define CHANNEL_2      (2)

/*Stop timer*/
#define TIMER_PRESCALER_STOP       (0xF8)

/*Timer pre-scalers*/
#define TIMER_PRESCALER_1    (1)
#define TIMER_PRESCALER_8    (2)
#define TIMER_PRESCALER_64   (3)
#define TIMER_PRESCALER_256  (4)
#define TIMER_PRESCALER_1024 (5)

/*Fast PWM frequencies*/
#define TIMER_FREQ_31_25KHZ  (TIMER_PRESCALER_1)
#define TIMER_FREQ_3_9KHZ    (TIMER_PRESCALER_8)
#define TIMER_FREQ_500HZ     (TIMER_PRESCALER_64)
#define TIMER_FREQ_122HZ     (TIMER_PRESCALER_256)
#define TIMER_FREQ_30HZ      (TIMER_PRESCALER_1024)

/*Phase correct frequencies*/
#define PHASE_CORRECT_OFFSET (10)
#define TIMER_FREQ_15_6KHZ   (TIMER_PRESCALER_1 + PHASE_CORRECT_OFFSET)
#define TIMER_FREQ_2KHZ      (TIMER_PRESCALER_8 + PHASE_CORRECT_OFFSET)
#define TIMER_FREQ_250HZ     (TIMER_PRESCALER_64 + PHASE_CORRECT_OFFSET)
#define TIMER_FREQ_61HZ      (TIMER_PRESCALER_256 + PHASE_CORRECT_OFFSET)
#define TIMER_FREQ_15HZ      (TIMER_PRESCALER_1024 + PHASE_CORRECT_OFFSET)

/*Custom PWM channels*/
#define TIMER_PWM_CHANNEL_A  (0)
#define TIMER_PWM_CHANNEL_B  (1)

/********************************************************************************/

void TIMER_voidStartTimer(uint8 Copy_u8Channel);

void Timer_voidStopTimer(uint8 Copy_u8channel);

/*This function is used to initialize a specific timer channel in delay mode*/
void TIMER_voidInitDelay(uint8 Copy_u8Channel);

/*This function is used to initialize a specific PWM signal with specific frequency*/
void TIMER_voidInitPWM(uint8 Copy_u8Channel, uint8 Copy_u8Frequency);

/*This function is used to generate custom frequency PWM signal*/
void TIMER_voidInitCustomFreqPWM(uint16 Copy_u16PeriodicTime_us);

/*This function is used to generate delay period in milliseconds (Synchronous mode)*/
void TIMER_voidDelayMs_Sync(uint8 Copy_u8Channel, uint32 Copy_u8DelayPeriodMs);

/*This function is used to generate delay period in milliseconds (Synchronous mode)*/
void TIMER_voidDelayMs_Async(uint8 Copy_u8Channel, uint32 Copy_u8DelayPeriodMs, void(*pfunc)(void));

/*This function is used to run a specific PWM signal with chosen duty cycle over a specific channel*/
void TIMER_voidRunPWM(uint8 Copy_u8Channel, uint8 Copy_u8DutyCycle);

/*This function is used to run custom frequency PWM signal with 16-bits duty cycle at specific channel [A or B]*/
void TIMER_voidRuncustomFreqPWM(uint8 Copy_u8CustomPWMChannel, uint16 Copy_u16DutyCycle);

/*This function is used to stop the PWM signal generation*/
void mtimer_voidStopPWM(uint8 Copy_u8Channel);


#endif /* TIMER_INTERFACE_H_ */