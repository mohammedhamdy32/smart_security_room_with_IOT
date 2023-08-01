/*
 * seven_segment.h
 *
 *  Created on: Oct 11, 2022
 *      Author: mohammedhamdy32
 */

#include "gpio.h"
#include "std_types.h"

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

/*define it if you use decoder*/
#define SEGMENT7_WITH_DECODER
//#undef  SEGMENT7_WITH_DECODER

/*the port of the 7_segment*/
#define SEGMENT7_PORT_ID      PORTB_ID
/*pins of 7 segment*/
#define SEGMENT7_PIN0_ID      PIN0_ID
#define SEGMENT7_PIN1_ID      PIN1_ID
#define SEGMENT7_PIN2_ID      PIN2_ID
#define SEGMENT7_PIN3_ID      PIN4_ID
#define SEGMENT7_PIN4_ID      PIN5_ID
#define SEGMENT7_PIN5_ID      PIN6_ID
#define SEGMENT7_PIN6_ID      PIN7_ID


void SevenSegment_display(uint8 value);


#endif /* SEVEN_SEGMENT_H_ */
