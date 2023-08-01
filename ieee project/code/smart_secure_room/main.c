/*
 * main.c
 *
 *  Created on: Jul 20, 2023
 *      Author: mohammedhamdy32
 */

#include "avr/io.h"
#include "avr/interrupt.h"
#include "gpio.h"
#include "std_types.h"
#include "seven_segment.h"
#include "avr/delay.h"
#include "ADC.h"
#include "lcd.h"
#include "UART.h"


uint8 INT0_flage = 0;
uint8 INT1_flage = 0;

int counter = 0;

int co2_flage = 0 , x;

#define  co2_id         49
#define  frame_id       50
#define  temprature_id  51
#define  FIRE_IS_DETECTED  52
#define  GAS_IS_DETECTED   53
#define  COUNTER_ID        54


int main()
{

	SREG = SREG | (1<<7);       /*open the global intrrupt */


	GPIO_setupPinDirection( PORTA_ID , PIN5_ID,  OUTPUT );
	GPIO_setupPinDirection( PORTA_ID , PIN6_ID,  OUTPUT );

	GPIO_setupPinDirection( PORTA_ID , PIN4_ID,  INPUT );

	GPIO_setupPinDirection( PORTD_ID , PIN2_ID,  INPUT );
	GPIO_setupPinDirection( PORTD_ID , PIN3_ID,  INPUT );


	MCUCR |= (1<<0) | (1<<1) | (1<<2) | (1<<3);
	GICR  |= (1<<6) | (1<<7);

	/* Enable the 7 segment */
	GPIO_setupPinDirection( PORTB_ID , PIN6_ID , OUTPUT );
	GPIO_writePin( PORTB_ID , PIN6_ID , 0 );

	ADC_config congif = { AVCC_PIN_5V , DIVITION_FACTOR_128 , FREE_RUNNIING_MODE };
	ADC_init( &congif );
	//	ADC_open();


	//	LCD_init();

	UART_configType config = { DISABLE , ONE_BIT , BIT8 , 9600 } ;
	UART_init( &config);

	uint8 temprature , light_intensty , CO2 , flame ;
	GPIO_setupPinDirection( PORTC_ID , PIN6_ID , OUTPUT );


	while(1)
	{


		ADMUX = 0;
		ADMUX |= (1<<REFS0);

		ADMUX=(ADMUX&0XE0) | (7&0X01);


		temprature = ADC_Single_ended_read_channel(ADC1);
		temprature = 	(temprature*5/1024.0)*100.0;

		_delay_ms(1000);
		UART_sendByte(COUNTER_ID);
//		_delay_ms(5);
		UART_sendByte(counter);
		SevenSegment_display(counter);
		_delay_ms(1000);

		UART_sendByte(temprature_id);
		_delay_ms(100);
		UART_sendByte(temprature);

		_delay_ms(100);



		CO2 = ADC_Single_ended_read_channel(ADC2);
		//		CO2  = 100 - ( (light_intensty/500.0)*100.0 ) ;

		UART_sendByte(co2_id);
		_delay_ms(100);
		UART_sendByte(CO2);

		_delay_ms(100);


		flame = ADC_Single_ended_read_channel(ADC3);

		UART_sendByte(frame_id);
		_delay_ms(100);
		UART_sendByte(flame);
		_delay_ms(100);




		if( ! (PINA & (1<<4)) )
		{
			GPIO_writePin( PORTC_ID , PIN6_ID , 1 );
			UART_sendByte( FIRE_IS_DETECTED ) ;
		}

		_delay_ms(100);



		if( CO2 > 200 || co2_flage == 1 )
		{
			GPIO_writePin( PORTC_ID , PIN6_ID , 1 );
			co2_flage = 1;
			UART_sendByte( GAS_IS_DETECTED );
		}

		_delay_ms(100);



		//		LCD_integerToString(CO2);

		//		_delay_ms(2000);
		//		_delay_ms(2000);
		//		_delay_ms(2000);






	}

}



ISR(INT0_vect)
{
	if( INT1_flage == 1 )
	{
		INT1_flage = 0;
		if(counter != 0)
			counter--;

		while( PORTD & (1<<2 )  );
		_delay_ms(500);

	}else
	{
		INT0_flage = 1;
	}

}

ISR(INT1_vect)
{
	if( INT0_flage == 1 )
	{
		INT0_flage = 0;
		counter ++;

		while( PORTD & (1<<3 )  );
		_delay_ms(500);

	}else
	{
		INT1_flage = 1;
	}
	_delay_ms(10);

}


