#pragma once

#ifndef DIO_H_
#define DIO_H_

#include "COMMON.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/******************************************************************************
*                      Functions Prototypes                                  *
******************************************************************************/
extern E_Status DIO_ErrorCheck(uint8 pin_number);
extern E_Status DIO_InitPin(volatile uint8* port_id, volatile uint8* port_dir
	, uint8 pin_number, uint8 pin_mode);
extern E_Status DIO_ReadPin(volatile uint8* pin_id, uint8 pin_number
	, uint8 *data);
extern E_Status DIO_WritePin(volatile uint8* port_id, uint8 pin_number
	, uint8 data);
extern E_Status DIO_InitInterrupt(uint8 interrupt_number, uint8 interrupt_mode);
extern E_Status DIO_ClearInterrupt(uint8 port_id, uint8 pin_number);
extern void DIO_WritePort(volatile uint8* port_id, uint8 data);

#endif /* DIO_H_ */