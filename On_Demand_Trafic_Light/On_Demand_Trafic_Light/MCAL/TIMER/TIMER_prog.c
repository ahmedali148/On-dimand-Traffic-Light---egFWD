/*
 * TIMER_prog.c
 *
 * Created: 06/11/2022 04:53:26 م
 *  Author: M
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"


/*Global variable used to carry pre-scaler value of timer0*/
static uint8 Global_u8timer0_prescaler;

/*Global variable used to carry pre-scaler value of timer1*/
static uint8 Global_u8timer1_prescaler;

/*Global variable used to carry pre-scaler value of timer2*/
static uint8 Global_u8timer2_prescaler;

/*Global variable used to save delay period in asynchronous operation for timer0*/
static uint32 Global_u32timer0_delayPeriod;

/*Global variable used to save delay period in asynchronous operation for timer1*/
static uint32 Global_u32timer1_delayPeriod;

/*Global variable used to save delay period in asynchronous operation for timer2*/
static uint32 Global_u32timer2_delayPeriod;

/*Global variable used to save Remaining time in synchronous operation for timers*/
uint32 Global_u32timers_remainingTime;

/*Global pointer to function used to process timer0 callback function*/
static void(*Globalfunc_timer0_ISR)(void) = NULL;

/*Global pointer to function used to process timer1 callback function*/
static void(*Globalfunc_timer1_ISR)(void) = NULL;

/*Global pointer to function used to process timer2 callback function*/
static void(*Globalfunc_timer2_ISR)(void) = NULL;


void TIMER_voidStartTimer(uint8 Copy_u8Channel)
{
	switch(Copy_u8Channel)
	{
		case CHANNEL_0: TCCR0 &= TIMER_PRESCALER_STOP; // Stopping timer0
		                TCNT0 = 0;// Resetting timer/counter register
						TCCR0 |= Global_u8timer0_prescaler; /*Starting timer0*/ break;
						
		case CHANNEL_1: TCCR1 &= 0xFFF8; // Stopping timer1
		                TCNT1 = 0;// Starting timer/counter register
		                TCCR1 |= Global_u8timer1_prescaler; /*Starting timer1*/ break;
		
		case CHANNEL_2:    /*Breaking from this case*/                     break;
						
		default:        /*do nothing*/                                     break;				
	}
	
}

void Timer_voidStopTimer(uint8 Copy_u8channel)
{
	/*Switching over timer channels*/
	switch(Copy_u8channel)
	{
		case CHANNEL_0: TCCR0 &= TIMER_PRESCALER_STOP; /*Stopping timer0*/ break;

		case CHANNEL_1:  /*Breaking from this case*/                       break;

		case CHANNEL_2:  /*Breaking from this case*/                       break;

		default:         /*Do nothing*/                                    break;
	}
}

/*This function is used to initialize a specific timer channel in delay mode*/
void TIMER_voidInitDelay(uint8 Copy_u8Channel)
{
    	switch(Copy_u8Channel)
    	{
	    	case CHANNEL_0: Global_u8timer0_prescaler = TIMER_PRESCALER_64; /*Setting the timer0 pre-scaler to be used in start timer function*/
			                TCCR0 = 0x08; /*Activation of CTC mode*/
							OCR0 = 125; /*Setting OCR value to make a delay by 1ms at 64 pre-scaler and clock frequency 8MHz*/
							break;
	    	case CHANNEL_1: Global_u8timer1_prescaler = TIMER_PRESCALER_64; /*Setting the timer1 pre-scaler to be used in start timer function*/
                            break;
	    	case CHANNEL_2: Global_u8timer2_prescaler = TIMER_PRESCALER_64; /*Setting the timer2 pre-scaler to be used in start timer function*/
	                    	break;							
            default:        break;

    	}	
}

/*This function is used to initialize a specific PWM signal with specific frequency*/
void TIMER_voidInitPWM(uint8 Copy_u8Channel, uint8 Copy_u8Frequency)
{	
		/*Switching over timer channels*/
		switch(Copy_u8Channel)
		{
			/*In case of timer0 channel*/
			case CHANNEL_0:

			/*Setting the timer0 pre-scaler to be used in start timer function*/
			Global_u8timer0_prescaler = Copy_u8Frequency;

			/*Switching over frequency value*/
			switch(Copy_u8Frequency)
			{
				/*In case of choosing fast PWM*/
				case TIMER_FREQ_31_25KHZ ... TIMER_FREQ_30HZ:

				/*Choosing fast PWM mode with non-inversion*/
				TCCR0 = 0x68;
				break;

				/*In case of choosing phase correct PWM*/
				case TIMER_FREQ_15_6KHZ ... TIMER_FREQ_15HZ:

				/*Removing the phase correct offset*/
				Global_u8timer0_prescaler -= PHASE_CORRECT_OFFSET;

				/*Choosing phase correct PWM mode with non-inversion*/
				TCCR0 = 0x60;
				break;

				/*In case of default*/
				default:     /*Do nothing*/             break;

			}

			/*Breaking from this case*/
			break;

			/*In case of timer1 channel*/
			case CHANNEL_1: /*Breaking from this case*/ break;

			/*In case of timer2 channel*/
			case CHANNEL_2: /*Breaking from this case*/ break;

			/*In case of default*/
			default:       /*Do nothing*/               break;

		}
}

/*This function is used to generate custom frequency PWM signal*/
void TIMER_voidInitCustomFreqPWM(uint16 Copy_u16PeriodicTime_us)
{
		/*Setting non-inversion mode in channel A and B, selecting phase correct PWM with top at ICR1 (mode 10)*/
		TCCR1 = 0xA210;

		/*Setting the periodic time of the signal*/
		ICR1 = Copy_u16PeriodicTime_us / 2;

		/*Setting timer1 prescaler to get 1us tick*/
		Global_u8timer1_prescaler = TIMER_PRESCALER_8;
}


/*This function is used to generate delay period in milliseconds (Synchronous mode)*/
void TIMER_voidDelayMs_Sync(uint8 Copy_u8Channel, uint32 Copy_u8DelayPeriodMs)
{
	switch(Copy_u8Channel)
	{
		/*In case of timer0 channel*/
		case CHANNEL_0:

		/*Starting timer channel 0*/
		TIMER_voidStartTimer(CHANNEL_0);

		/*Looping over delay period*/
		while(Copy_u8DelayPeriodMs--)
		{
			/*Waiting until 1ms of delay passes*/
			while(!GET_BIT(TIFR, 1));
			Global_u32timers_remainingTime = Copy_u8DelayPeriodMs;

			/*CLearing compare match flag bit*/
			SET_BIT(TIFR, 1);
		}

		/*Stopping timer channel 0*/
		TIMER_voidStartTimer(CHANNEL_0);
		break;
		
		/*In case of timer1 channel*/
		case CHANNEL_1: /*Breaking from this case*/ break;

		/*In case of timer2 channel*/
		case CHANNEL_2: /*Breaking from this case*/ break;

		/*In case of default*/
		default:       /*Do nothing*/               break;
	}
}

/*This function is used to generate delay period in milliseconds (Synchronous mode)*/
void TIMER_voidDelayMs_Async(uint8 Copy_u8Channel, uint32 Copy_u8DelayPeriodMs, void(*pfunc)(void))
{
	/*Enable global interrupts*/
	SET_BIT(SREG, 7);

	/*Switching over timer channels*/
	switch(Copy_u8Channel)
	{
		/*In case of timer0 channel*/
		case CHANNEL_0:

		/*Saving the delay period to check over it at the ISR*/
		Global_u32timer0_delayPeriod = Copy_u8DelayPeriodMs;

		/*Setting the call back function address*/
		Globalfunc_timer0_ISR = pfunc;

		/*Enable compare match interrupt*/
		SET_BIT(TIMSK, 1);

		/*Starting timer channel 0*/
		TIMER_voidStartTimer(CHANNEL_0);

		/*Breaking from this case*/
		break;

		/*In case of timer1 channel*/
		case CHANNEL_1:

		/*Saving the delay period to check over it at the ISR*/
		Global_u32timer1_delayPeriod = Copy_u8DelayPeriodMs;

		/*Setting the call back function address*/
		Globalfunc_timer1_ISR = pfunc;

		/*Breaking from this case*/
		break;

		/*In case of timer2 channel*/
		case CHANNEL_2:

		/*Saving the delay period to check over it at the ISR*/
		Global_u32timer2_delayPeriod = Copy_u8DelayPeriodMs;

		/*Setting the call back function address*/
		Globalfunc_timer2_ISR = pfunc;

		/*Breaking from this case*/
		break;

		/*In case of default*/
		default:

		/*Breaking from default case*/
		break;
	}
}

/*This function is used to run a specific PWM signal with chosen duty cycle over a specific channel*/
void TIMER_voidRunPWM(uint8 Copy_u8Channel, uint8 Copy_u8DutyCycle)
{
	/*Switching over timer channels*/
	switch(Copy_u8Channel)
	{
		/*In case of timer0 channel*/
		case CHANNEL_0:

		/*Setting the duty cycle*/
		OCR0 = Copy_u8DutyCycle;

		/*Starting timer channel 0*/
		TIMER_voidStartTimer(CHANNEL_0);
		break;

		/*In case of timer1 channel*/
		case CHANNEL_1: /*Breaking from this case*/ break;

		/*In case of timer2 channel*/
		case CHANNEL_2: /*Breaking from this case*/ break;

		/*In case of default*/
		default:       /*Do nothing*/               break;
	}
}

/*This function is used to run custom frequency PWM signal with 16-bits duty cycle at specific channel [A or B]*/
void TIMER_voidRuncustomFreqPWM(uint8 Copy_u8CustomPWMChannel, uint16 Copy_u16DutyCycle)
{
	/*Switching over custom PWM channels*/
	switch(Copy_u8CustomPWMChannel)
	{
		/*In case of choosing channel A*/
		case TIMER_PWM_CHANNEL_A:

		/*Setting the duty cycle*/
		OCR1A = Copy_u16DutyCycle;

		/*Break from this case*/
		break;

		/*In case of choosing channel B*/
		case TIMER_PWM_CHANNEL_B:

		/*Setting the duty cycle*/
		OCR1B = Copy_u16DutyCycle;
		break;

		/*In case of default*/
		default:

		/*Breaking from default case*/
		break;
	}

	/*Starting timer1*/
	TIMER_voidStartTimer(CHANNEL_1);
}

/*This function is used to stop the PWM signal generation*/
void mtimer_voidStopPWM(uint8 Copy_u8Channel)
{
		switch(Copy_u8Channel)
		{
			/*In case of timer0 channel*/
			case CHANNEL_0:

			/*Stopping timer channel 0*/
			Timer_voidStopTimer(CHANNEL_0);
			break;

		/*In case of timer1 channel*/
		case CHANNEL_1: /*Breaking from this case*/ break;

		/*In case of timer2 channel*/
		case CHANNEL_2: /*Breaking from this case*/ break;

		/*In case of default*/
		default:       /*Do nothing*/               break;
		}
}


/************************************************************************************************/
/*                                              Timer ISRs                                      */
/************************************************************************************************/

/*Timer0 compare match interrupt service routine (ISR)*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	/*Checking if the call back pointer has an address of function or not*/
	if(Globalfunc_timer0_ISR != NULL)
	{
		/*Checking if the delay period has passed or not*/
		if(Global_u32timer0_delayPeriod)
		{
			/*Decrementing delay period*/
			Global_u32timer0_delayPeriod--;
		}
		else
		{
			/*Executing the call back function*/
			Globalfunc_timer0_ISR();

			/*Disable the compare match interrupt*/
			CLR_BIT(TIMSK, 1);

			/*Stopping the timer*/
			Timer_voidStopTimer(CHANNEL_0);
		}
	}
}
