/*
 * UART.c
 *
 *  Created on: Oct 14, 2022
 *      Author: mohammedhamdy32
 */

#include "UART.h"
#include "avr/io.h"
#include "common_macros.h"

void UART_init(UART_configType *configPtr)
{
	uint8 ubrr_value;
	UCSRA= (1<<U2X);
	/*Double the USART Transmission Speed*/
	UCSRB = (1<<RXEN) | (1<<TXEN) | ( (GET_BIT(configPtr->char_size,2))<<2 );
	/*
	 RXEN Enable the RX
	 TXEN Enable the TX
	 */
	UCSRC = (1<<URSEL) | ( (configPtr->stop_bit)<<USBS)
					| ((GET_BIT(configPtr->char_size,0))<< 1) | ( (GET_BIT(configPtr->char_size,1))<<2 );
	UCSRC = (UCSRC & 0xCF) | ( (configPtr->parity_mode)<<4 );

	/*
	 UCSZ1 , UCSZ0 To make it 8 data bit
	 URSEL , The URSEL must be one when writing the UCSRC
	 Asynchronous operation
	 Parity mode is disable
	 1 bit for stop bit
	 */
	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (configPtr->baud_rate * 8UL))) - 1);/*equation in data sheet*/

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}


void UART_sendByte(uint8 const data)
{

#if 0
	UDR = data;
	/*This bit is set when all bits are shifted in shift register and there is no bits in UDR to be shifted*/
	while(BIT_IS_CLEAR(UCSRA,TXC));
	/*we make polling to make sure that we didn't end the function until all bits are shifted to shift register*/
	SET_BIT(UCSRA,TXC);
	/*To clear the flag*/
#else
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	/*This bit is set if the transimeter is ready to receive another byte*/
	UDR = data;
#endif
}

uint8 UART_recieveByte(void)
{
	/*To wait until this bit is 1 ,becase this bit is set when
	  there are data which is ready to be read in UDR*/
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;
}

void UART_sendString(const uint8 *str)
{
	uint16 i=0;
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}

}


void UART_recieveString(uint8 *str)
{
	uint16 i=0;
	str[i]=UART_recieveByte();

	while('#' != str[i++]){
		str[i]=UART_recieveByte();
	  }

	str[i]='\0';
}
