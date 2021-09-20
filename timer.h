#ifndef TIMER_H_
#define TIMER_H_
#include "common.h"
/******************************************************************************
*                         Types Declaration                                  *
******************************************************************************/
typedef enum
{
	TIMER_0, TIMER_1, TIMER_2
}TIMER_Type;
typedef enum
{
	/* MASK = 0xF8 */
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}TIMER_Clock;
typedef enum
{
	/* TIMER0 MASK = 0xCF */
	/* TIMER1 MASK COM1B --> = 0xCF */
	/* TIMER1 MASK COM1A --> = 0x3F */
	NORMAL_COM, TOGGLE_RESERVED, CLEAR_COM, SET_COM
}TIMER_CompareOutputMode;

typedef enum
{
	/* MASK = 0xB7 */
	NORMAL_MODE, PWM_PHASE_CORRECT_MODE, CTC_MODE, FAST_PWM_MODE
}TIMER0_Mode;
typedef enum
{
	DISABLE_OVERFLOW_INTERRUPT, ENABLE_OVERFLOW_INTERRUPT
} TIMER0_OverflowInterrupt;
typedef enum
{
	DISABLE_COMPARE_INTERRUPT, ENABLE_COMPARE_INTERRUPT
} TIMER0_CompareInterrupt;

typedef enum
{
	/* REGISTER TCCR1A , BITS WGM11/WGM10 , MASK = 0xFC */
	NORMAL_0, PWM_PHASE_8BIT_0, PWM_PHASE_9BIT_0, PWM_PHASE_10BIT_0
	, CTC_OCR1A_0 = 0, FAST_PWM_8BIT_0, FAST_PWM_9BIT_0, FAST_PWM_10BIT_0
	, PWM_PHASE_FREQUENCY_ICR1_0 = 0, PWM_PHASE_FREQUENCY_OCR1A_0
	, PWM_PHASE_CORRECT_ICR1_0, PWM_PHASE_CORRECT_OCR1A_0
	, CTC_ICR1_0 = 0, RESERVED_0, FAST_PWM_ICR1_0, FAST_PWM_OCR1A_0
} TIMER1_MODE_01;
typedef enum
{
	/* REGISTER TCCR1B , BITS WGM13/WGM12 , MASK = 0xE7 */
	NORMAL_2 = 0, PWM_PHASE_8BIT_2 = 0, PWM_PHASE_9BIT_2 = 0, PWM_PHASE_10BIT_2 = 0
	, CTC_OCR1A_2 = 1, FAST_PWM_8BIT_2 = 1, FAST_PWM_9BIT_2 = 1, FAST_PWM_10BIT_2 = 1
	, PWM_PHASE_FREQUENCY_ICR1_2 = 2, PWM_PHASE_FREQUENCY_OCR1A_2 = 2
	, PWM_PHASE_CORRECT_ICR1_2 = 2, PWM_PHASE_CORRECT_OCR1A_2 = 2
	, CTC_ICR1_2 = 3, RESERVED_2 = 3, FAST_PWM_ICR1_2 = 3, FAST_PWM_OCR1A_2 = 3
} TIMER1_MODE_23;
typedef enum
{
	DISABLE_INPUT_CAPTURE_INTERRUPT, ENABLE_INPUT_CAPTURE_INTERRUPT
} TIMER1_InputCaptureInterrupt;
typedef enum
{
	DISABLE_COMPARE_INTERRUPT_A, ENABLE_COMPARE_INTERRUPT_A
} TIMER1_CompareInterrupt_A;
typedef enum
{
	DISABLE_COMPARE_INTERRUPT_B, ENABLE_COMPARE_INTERRUPT_B
} TIMER1_CompareInterrupt_B;
typedef enum
{
	DISABLE_TIMER1_OVERFLOW_INTERRUPT, ENABLE_TIMER1_OVERFLOW_INTERRUPT
} TIMER1_OverflowInterrupt;
typedef enum
{
	FALLING, RISING
}TIMER1_EdgeType;
typedef struct
{
	TIMER_Type timer_type;
	TIMER_Clock timer_clock;
	TIMER_CompareOutputMode timer_com;
	TIMER0_Mode timer0_mode;
	TIMER0_OverflowInterrupt timer0_overflow_interrupt;
	TIMER0_CompareInterrupt timer0_compare_interrupt;
	TIMER1_MODE_01 timer1_mode_01;
	TIMER1_MODE_23 timer1_mode_23;
	TIMER1_InputCaptureInterrupt timer1_input_cap_int;
	TIMER1_CompareInterrupt_A timer1_compare_int_A;
	TIMER1_CompareInterrupt_B timer1_compare_int_B;
	TIMER1_OverflowInterrupt timer1_overflow_int;
	TIMER1_EdgeType edge;
} TIMER_ConfigType;

/******************************************************************************
*                      Functions Prototypes                                  *
******************************************************************************/
extern void TIMER_init(TIMER_ConfigType* Config_Ptr);
extern void TIMER_reset(TIMER_ConfigType* Config_Ptr);
extern void TIMER_stop(TIMER_ConfigType* Config_Ptr);
extern void TIMER_start(TIMER_ConfigType* Config_Ptr);



#endif /* TIMER_H_ */