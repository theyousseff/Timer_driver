#include "DIO.h"

uint8 g_interruptRegisterMap[4] = { INT0, INT1, INT2 };

/*******************************************************
* .Name: DIO_ErrorCheck
* .Inputs: pin_number
* .Outputs: None
* .Return Value: Error Status
* .Description: Check for invalid inputs
* ****************************************************/
E_Status DIO_ErrorCheck(uint8 pin_number)
{
	E_Status e_status = E_OK;
	/* Error Checking */
	if ((PIN_0 > pin_number) || (PIN_7 < pin_number)) /* Undefined Pin */
	{
		e_status = E_NOK;
	}

	return e_status;
}

/************************************************************************
* .Name: DIO_InitPin
* .Inputs: port_id, port_dir, pin_number, pin_mode
* .Outputs: None
* .Return Value: Error Status
* .Description: Initialize DIO pins as INPUT_PULLUP/INPUT_PULLDOWN/OUTPUT
* ***********************************************************************/
E_Status DIO_InitPin(volatile uint8* port_id, volatile uint8* port_dir,
	uint8 pin_number, uint8 pin_mode)
{
	E_Status e_status1 = E_OK;
	if ((OUTPUT != pin_mode) && (INPUT != pin_mode) \
		&& (INPUT_PULLUP != pin_mode) && (INPUT_PULLDOWN != pin_mode))
	{
		/* Undefined Mode */
		e_status1 = E_NOK;
	}
	if (E_OK == e_status1)
	{
		/* Check for invalid port or pin */
		e_status1 = DIO_ErrorCheck(pin_number);
	}
	if (E_OK == e_status1)
	{
		if (OUTPUT == pin_mode)
		{
			/* Set pin as output (positive logic) (DDRA, DDRB, DDRC, DDRD) */
			*port_dir |= pin_number;
			/* Clear pin before starting (PORTA, PORTB, PORTC , PORTD) */
			*port_id &= ~pin_number;
		}
		else if (INPUT == pin_mode || INPUT_PULLDOWN == pin_mode)
		{
			*port_dir &= ~pin_number;
		}
		else if (INPUT_PULLUP == pin_mode)
		{
			*port_dir &= ~pin_number;
			*port_id |= pin_number;
		}
	}

	return e_status1;
}

/*********************************************************************
* .Name: DIO_ReadPin
* .Inputs: pin_id, pin_number
* .Outputs: data
* .Return Value: Error Status
* .Description: Read Pin Data Register
* **********************************************************************/
E_Status DIO_ReadPin(volatile uint8* pin_id, uint8 pin_number, uint8 *data)
{
	E_Status e_status2 = E_OK;
	e_status2 = DIO_ErrorCheck(pin_number);

	*data = (*pin_id & pin_number); /* Read Data */

	return e_status2;
}

/*********************************************************************
* .Name: DIO_WritePin
* .Inputs: port_id, pin_number, data
* .Outputs: None
* .Return Value: Error Status
* .Description: Write On Pin Data Register
* **********************************************************************/
E_Status DIO_WritePin(volatile uint8* port_id, uint8 pin_number, uint8 data)
{
	E_Status e_status3 = E_OK;
	e_status3 = DIO_ErrorCheck(pin_number);

	if (data == HIGH)
	{
		*port_id |= (1 << pin_number);  /* Set Pin */
	}
	else if (data == LOW)
	{
		*port_id &= ~(1 << pin_number); /* Clear Pin */
	}

	return e_status3;
}
/*********************************************************************
* .Name: DIO_WritePort
* .Inputs: port_id, pin_number, data
* .Outputs: None
* .Return Value: None
* .Description: Write data on the entire port register
* **********************************************************************/
void DIO_WritePort(volatile uint8* port_id, uint8 data)
{
	*port_id = data; /* Write data to PORT */
}
/************************************************************************
* .Name: DIO_InitInterrupt
* .Inputs: interrupt_number, interrupt_mode
* .Outputs: None
* .Return Value: Error Status
* .Description: Initialization of Interrupt Mode and Event Type for Pin
* ********************************************************************/
E_Status DIO_InitInterrupt(uint8 interrupt_number, uint8 interrupt_mode)
{
	E_Status e_status4 = E_OK;
	uint8 isc0 = 0, isc1 = 0;

	SREG &= ~(1 << 7); /* Disable interrupts by clearing I-bit */

					   /*Enable external interrupt pin INT0/INT1/INT2*/
	GICR |= (1 << g_interruptRegisterMap[interrupt_number]);

	if (INTERRUPT2 == interrupt_number)
	{
		if (RISING_EDGE == interrupt_mode)
		{
			MCUCSR |= (1 << ISC2);   /* Trigger INT2 with the rising edge */
		}
		else if (FALLING_EDGE == interrupt_mode)
		{
			MCUCSR |= (1 << ISC2);   /* Trigger INT2 with the falling edge */
		}
	}
	else
	{
		if (INTERRUPT0 == interrupt_number)
		{
			isc0 = ISC00;
			isc1 = ISC01;
		}
		else if (INTERRUPT1 == interrupt_number)
		{
			isc0 = ISC10;
			isc1 = ISC11;
		}

		if (RISING_EDGE == interrupt_mode)
		{
			/* Trigger INT0 or INT1 with the rising edge */
			MCUCR |= (1 << isc0) | (1 << isc1);
		}
		else if (FALLING_EDGE == interrupt_mode)
		{
			/* Trigger INT0 or INT1 with the falling edge */
			MCUCR |= (1 << isc1);
			MCUCR &= ~(1 << isc0);
		}
		else
		{
			e_status4 = E_NOK; /* Error Wrong Input */
		}
	}
	SREG |= (1 << 7);  /*Enable interrupts by setting I-bit */

	return e_status4;
}