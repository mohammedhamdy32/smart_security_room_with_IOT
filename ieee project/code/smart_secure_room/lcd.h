/*
 * lcd.h
 *
 *  Created on: Oct 4, 2022
 *      Author: mohammedhamdy32
 */


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "gpio.h"
#include <util/delay.h>


#define LCD_MODE        4
/*Data port*/

#define LCD_DATA_PORT_ID   PORTB_ID
/*pins of 8 bit data pins*/
#define LCD_DATA_Pin0
#define LCD_DATA_PIN1
#define LCD_DATA_PIN2
#define LCD_DATA_PIN3
#define LCD_DATA_PIN4    PIN0_ID
#define LCD_DATA_PIN5    PIN1_ID
#define LCD_DATA_PIN6    PIN2_ID
#define LCD_DATA_PIN7    PIN4_ID



/*Rs port and pin*/
#define LCD_RS_PORT_ID  PORTA_ID
#define LCD_RS_PIN_ID   PIN3_ID

/*enable port and pin*/
#define LCD_ENABLE_PORT_ID   PORTA_ID
#define LCD_ENABLE_PIN_ID    PIN2_ID

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

void LCD_writeChar(uint8 ch);
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_writeString(uint8 *str);
void LCD_moveCursor(uint8 row , uint8 col);
void LCD_integerToString(uint8 num);
void LCD_clearScreen();









/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


#endif
