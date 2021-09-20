#include "TIMER.h"
#include "DIO.h"



void TIMER_init(TIMER_ConfigType* Config_Ptr)
{
	if (Config_Ptr->timer_type == TIMER_0)
	{
		if (Config_Ptr->timer0_mode == FAST_PWM_MODE || Config_Ptr->timer0_mode == PWM_PHASE_CORRECT_MODE)
		{
			OCR0 = 0;
			/* Set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
			DIO_InitPin(&PORTB, &DDRB, PIN_3, OUTPUT);
			TCCR0 = (0 << FOC0);
		}
		else
		{
			TCCR0 = (1 << FOC0);
		}
		TCNT0 = 0;
		TCCR0 = (TCCR0 & 0xB7) | (Config_Ptr->timer0_mode);
		TCCR0 = (TCCR0 & 0xCF) | (Config_Ptr->timer_com);
		TIMSK |= (Config_Ptr->timer0_compare_interrupt << OCIE0) | (Config_Ptr->timer0_overflow_interrupt << TOIE0);
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock);
		if ((Config_Ptr->timer0_compare_interrupt == ENABLE_COMPARE_INTERRUPT) || (Config_Ptr->timer0_overflow_interrupt == ENABLE_OVERFLOW_INTERRUPT))
		{
			/* Enable Global Interrupt I-Bit */
			SREG |= (1 << 7);
		}
	}
	else if (Config_Ptr->timer_type == TIMER_1)
	{
		if (Config_Ptr->timer1_mode_01 == NORMAL_0 || Config_Ptr->timer1_mode_01 == CTC_OCR1A_0 || Config_Ptr->timer1_mode_01 == CTC_ICR1_0)
		{
			/* For Non-PWM Mode */
			TCCR1A = (1 << FOC1A) | (1 << FOC1B);
		}
		else
		{
			/* Set PD4/OC1B & PD5/OC1A as output pins --> pins where the PWM signal is generated from MC.*/
			DIO_InitPin(&PORTD, &DDRD, PIN_4, OUTPUT);
			DIO_InitPin(&PORTD, &DDRD, PIN_5, OUTPUT);
		}
		TCNT1 = 0;	/* Set Timer initial value to 0 */
		ICR1 = 0; 	/* Initial Value for the input capture register */
		TCCR1A = (TCCR1A & 0xCF) | (Config_Ptr->timer_com);
		TCCR1A = (TCCR1A & 0x3F) | (Config_Ptr->timer_com);
		TCCR1A = (TCCR1A & 0xFC) | (Config_Ptr->timer1_mode_01);
		TCCR1B = (TCCR1B & 0xE7) | (Config_Ptr->timer1_mode_23);
		/* insert the required edge type in ICES1 bit in TCCR1B Register */
		TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge) << ICES1);
		TIMSK |= (Config_Ptr->timer1_input_cap_int << TICIE1) | (Config_Ptr->timer1_compare_int_A << OCIE1A)
			| (Config_Ptr->timer1_compare_int_B << OCIE1B) | (Config_Ptr->timer1_overflow_int << TOIE1);
		TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock);

		if ((Config_Ptr->timer1_compare_int_A == ENABLE_COMPARE_INTERRUPT_A) || (Config_Ptr->timer1_compare_int_B == ENABLE_COMPARE_INTERRUPT_B)
			|| (Config_Ptr->timer1_overflow_int == ENABLE_TIMER1_OVERFLOW_INTERRUPT) || (Config_Ptr->timer1_input_cap_int == ENABLE_INPUT_CAPTURE_INTERRUPT))
		{
			/* Enable Global Interrupt I-Bit */
			SREG |= (1 << 7);
		}
	}
	else if (Config_Ptr->timer_type == TIMER_2)
	{
		if (Config_Ptr->timer0_mode == FAST_PWM_MODE || Config_Ptr->timer0_mode == PWM_PHASE_CORRECT_MODE)
		{
			OCR0 = 0;
			/* Set PD7/OC2 as output pin --> pin where the PWM signal is generated from MC.*/
			DIO_InitPin(&PORTD, &DDRD, PIN_7, OUTPUT);
			TCCR2 = (0 << FOC0);
		}
		else
		{
			TCCR2 = (1 << FOC0);
		}
		TCNT2 = 0;
		TCCR2 = (TCCR2 & 0xB7) | (Config_Ptr->timer0_mode);
		TCCR2 = (TCCR2 & 0xCF) | (Config_Ptr->timer_com);
		TIMSK |= (Config_Ptr->timer0_compare_interrupt << OCIE2) | (Config_Ptr->timer0_overflow_interrupt << TOIE2);
		TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->timer_clock);

		if ((Config_Ptr->timer0_compare_interrupt == ENABLE_COMPARE_INTERRUPT) || (Config_Ptr->timer0_overflow_interrupt == ENABLE_OVERFLOW_INTERRUPT))
		{
			/* Enable Global Interrupt I-Bit */
			SREG |= (1 << 7);
		}
	}
}

/*******************************************************
* .Name: TIMER_reset
* .Inputs: None
* .Outputs: None
* .Return Value: None
* .Description: Resets Timer 0 or 1 or 2
* *****************************************************/
void TIMER_reset(TIMER_ConfigType* Config_Ptr)
{
	/* Set Timer initial value to 0 */
	if (Config_Ptr->timer_type == TIMER_0)
		TCNT0 = 0;
	else if (Config_Ptr->timer_type == TIMER_1)
		TCNT1 = 0;
	else if (Config_Ptr->timer_type == TIMER_2)
		TCNT2 = 0;
}

/*******************************************************
* .Name: TIMER_stop
* .Inputs: None
* .Outputs: None
* .Return Value: None
* .Description: Pauses Timer 0 or 1 or 2 Clock
* *****************************************************/
void TIMER_stop(TIMER_ConfigType* Config_Ptr)
{
	if (Config_Ptr->timer_type == TIMER_0)
		TCCR0 = (TCCR0 & 0xF8) | NO_CLOCK; 		/* Stop Timer0 Clock */
	else if (Config_Ptr->timer_type == TIMER_1)
		TCCR1B = (TCCR1B & 0xF8) | NO_CLOCK; 	/* Stop Timer1 Clock */
	else if (Config_Ptr->timer_type == TIMER_2)
		TCCR2 = (TCCR2 & 0xF8) | NO_CLOCK; 		/* Stop Timer2 Clock */
}

/*******************************************************
* .Name: TIMER_start
* .Inputs: None
* .Outputs: None
* .Return Value: None
* .Description: Resumes Timer 0 or 1 or 2 Clock
* *****************************************************/
void TIMER_start(TIMER_ConfigType* Config_Ptr)
{
	if (Config_Ptr->timer_type == TIMER_0)
		TCCR0 = (TCCR0 & 0xF8) | Config_Ptr->timer_clock; 	/* start Timer0 Clock */
	else if (Config_Ptr->timer_type == TIMER_1)
		TCCR1B = (TCCR1B & 0xF8) | Config_Ptr->timer_clock; /* start Timer1 Clock */
	else if (Config_Ptr->timer_type == TIMER_2)
		TCCR2 = (TCCR2 & 0xF8) | Config_Ptr->timer_clock; 	/* start Timer2 Clock */
}

