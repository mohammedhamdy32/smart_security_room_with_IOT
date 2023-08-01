/*
 * ADC.c
 *
 *  Created on: Apr 9, 2023
 *      Author: mohammedhamdy32
 */


#include "ADC.h"
#include "gpio.h"
#include "avr/io.h"
#include "common_macros.h"


void ADC_open(void)
{
	SET_BIT(ADCSRA,ADEN);  /*Enable the ADC*/
}

void ADC_close(void)
{
	CLEAR_BIT(ADCSRA,ADEN);  /*Enable the ADC*/
}

void ADC_init(ADC_config *config)
{

	ADMUX  = (config->Ref)<<6;
	ADCSRA = 0x87;  /*128 prescaler*/
	ADCSRA = (ADCSRA & 0XF8) | (config->pre_secaler);
	SFIOR  = (SFIOR  & 0X1F) | (config->mode)<<6;

}




/*If I used single ended input*/
#ifdef  SINGLE_ENDED_INPUT

uint16 ADC_Single_ended_read_channel(ADC_Single_endede_pins a_pin)
{
	GPIO_setupPinDirection(PORTA_ID, a_pin , INPUT); /*Make this pin Input*/
	ADMUX = (ADMUX & 0XE0) | (a_pin);
	SET_BIT(ADCSRA,ADSC);  /*Start Conversion*/
    while( !GET_BIT(ADCSRA,ADIF) ); /*Polling till the ADC completes Conversion*/
	CLEAR_BIT(ADCSRA,ADSC);  /*Stop Conversion*/
	SET_BIT(ADCSRA,ADIF); //TO clear the ADC flag

	return ADC;
}

#endif


/*If I used Differntial input*/
#ifdef  DIFFERENTIAL_INPUT

void ADC_Differntial_Input_Setup_ADC_pins(DIFFERENTIAL_INPUT a_pin)
{
	GPIO_setupPinDirection(PORTA_ID, a_pin , INPUT); /*Make this pin Input*/
	ADMUX = (ADMUX & 0XE0) | (a_pin);
}
#endif












