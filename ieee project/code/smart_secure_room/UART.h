/*
 * UART.h
 *
 *  Created on: Oct 14, 2022
 *      Author: mohammedhamdy32
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

 #undef F_CPU
 #define F_CPU 16000000

/*enum for parity*/
typedef enum{
	DISABLE,EVEN_PARITY=2,ODD_PARITY
}PARITY_MODE;

typedef enum{
	ONE_BIT,TWO_BIT
}STOP_BIT;

typedef enum{
	BIT5,BIT6,BIT7,BIT8,BIT9=7
}CHARACTER_SIZE;

/*config struct */
typedef struct{
	PARITY_MODE parity_mode;
	STOP_BIT stop_bit;
	CHARACTER_SIZE char_size;
	uint32 baud_rate;
}UART_configType;

void UART_init(UART_configType *configPtr);
void UART_sendByte(uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *str);
void UART_recieveString(uint8 *str);

#endif /* UART_H_ */
