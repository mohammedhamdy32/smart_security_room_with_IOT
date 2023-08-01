/*
 * ADC.h
 *
 *  Created on: Apr 9, 2023
 *      Author: mohammedhamdy32
 */

#ifndef ADC_H_
#define ADC_H_

#define  SINGLE_ENDED_INPUT
#define  DIFFERENTIAL_INPUT

#undef    DIFFERENTIAL_INPUT

#include "std_types.h"


/*ADC refrrence pin*/
typedef   enum { VREF_PIN , AVCC_PIN_5V  , INTERNAL_REFS_2_POINT_56_V=3  }ADC_REF;

/*The prescaler of ADC*/
typedef   enum { DIVITION_FACTOR_0 , DIVITION_FACTOR_2 ,DIVITION_FACTOR_4 ,DIVITION_FACTOR_8 , DIVITION_FACTOR_16 ,
               	 DIVITION_FACTOR_32 , DIVITION_FACTOR_64 , DIVITION_FACTOR_128 }ADC_Prescaler;

/*ADC Modes*/
typedef  enum{ FREE_RUNNIING_MODE , ANALOG_COMPARATOR_MODE , EXTERNAL_INTERRUNP , TIMER_0_COMP , TIMER_0_OVR,
               TIMER1_COMP , TIMER_1_OVR , TIMER_1_CAPTURE_EVENT }ADC_Auto_trigger_mode;


#ifdef  SINGLE_ENDED_INPUT
  /*ADC which pin?*/
  typedef   enum { ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7}ADC_Single_endede_pins;
#endif


#ifdef DIFFERENTIAL_INPUT
  /*ADC which two pins and what is the gain*/
  typedef   enum { ADC0_ADC0_10X = 8 , ADC1_ADC0_10X , ADC0_ADC0_200X , ADC1_ADC0_200X , ADC2_ADC2_10X , ADC3_ADC2_10X,
	               ADC2_ADC2_200X , ADC3_ADC2_200X , ADC0_ADC1_1X , ADC1_ADC1_1X , ADC2_ADC1_1X , ADC3_ADC1_1X ,
				   ADC4_ADC1_1X , ADC5_ADC1_1X , ADC6_ADC1_1X , ADC7_ADC1_1X , ADC0_ADC2_1X , ADC1_ADC2_1X , ADC2_ADC2_1X,
				   ADC3_ADC2_1X , ADC4_ADC2_1X , ADC5_ADC2_1X }ADC_Differial_pins;
#endif


/********* Struct **********/
typedef struct {
	ADC_REF Ref;
	ADC_Prescaler pre_secaler;
	ADC_Auto_trigger_mode  mode;

}ADC_config;


void ADC_init(ADC_config *config);
/*If I used single ended input*/
#ifdef  SINGLE_ENDED_INPUT
  uint16 ADC_Single_ended_read_channel(ADC_Single_endede_pins a_pin);
#endif


/*If I used Differntial input*/
#ifdef  DIFFERENTIAL_INPUT
  void ADC_Differntial_Input_Setup_ADC_pins(DIFFERENTIAL_INPUT a_pin);
#endif


#endif /* ADC_H_ */
