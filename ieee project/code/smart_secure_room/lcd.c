/*
 * lcd.c
 *
 *  Created on: Oct 4, 2022
 *      Author: mohammedhamdy32
 */

#include "lcd.h"
#include "common_macros.h" /* To use the macros like SET_BIT */



void LCD_sendCommand(uint8 command)
{

	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);     /*write 0 in RS pin */
	_delay_ms(1);

	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);   /*write 1 in enable pin */
	_delay_ms(1);

#if (LCD_MODE == 8)

	GPIO_writePort(LCD_DATA_PORT_ID, command); /*write the command in data port*/

	_delay_ms(1);

#else

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4 , GET_BIT(command,4) );
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN5 , GET_BIT(command,5) );
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN6 , GET_BIT(command,6) );
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN7 , GET_BIT(command,7) );

	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW); /*write 0 in enable pin to make falling edge*/
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH); /*write 1 in enable pin */
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4 , GET_BIT(command,0) );
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN5 , GET_BIT(command,1) );
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN6 , GET_BIT(command,2) );
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN7 , GET_BIT(command,3) );

	_delay_ms(1);



#endif

	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	/*write  0 in enable pin beacase LCD read the at falling edge of enable, so we make it 1 then 0*/

	_delay_ms(1);
}


void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,OUTPUT);/*make enable output*/

	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID,OUTPUT);/*make RS  output*/
	_delay_ms(20);

#if (LCD_MODE == 8)

	GPIO_setupPortDirection(PORTC_ID, OUTPUT); /*make portC output*/
	_delay_ms(20);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);  /*make LCD 8 bit mode and 2 line*/


#else
	GPIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_DATA_PIN4 , OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_DATA_PIN5 , OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_DATA_PIN6 , OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_DATA_PIN7 , OUTPUT);
	/*make last 4 pins in portc output*/
	_delay_ms(20);
	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif


	LCD_sendCommand(LCD_CURSOR_OFF);

	LCD_sendCommand(LCD_CLEAR_COMMAND);

}

void LCD_writeChar(uint8 ch)
{
	  GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);     /*write 1 in RS pin */
			_delay_ms(1);

			GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);   /*write 1 in enable pin */
			_delay_ms(1);

		#if (LCD_MODE == 8)

			GPIO_writePort(LCD_DATA_PORT_ID, ch); /*write the command in data port*/

			_delay_ms(1);

		#else

			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4 , GET_BIT(ch,4) );
			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN5 , GET_BIT(ch,5) );
			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN6 , GET_BIT(ch,6) );
			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN7 , GET_BIT(ch,7) );

			_delay_ms(1);
			GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW); /*write 0 in enable pin to make falling edge*/
			_delay_ms(1);
			GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH); /*write 1 in enable pin */
			_delay_ms(1);

			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN4 , GET_BIT(ch,0) );
			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN5 , GET_BIT(ch,1) );
			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN6 , GET_BIT(ch,2) );
			GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN7 , GET_BIT(ch,3) );

			_delay_ms(1);



		#endif

			GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
			/*write  0 in enable pin beacase LCD read the at falling edge of enable, so we make it 1 then 0*/

			_delay_ms(1);
}

void LCD_writeString(uint8 *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		LCD_writeChar(str[i]);
		i++;
	}
}

void LCD_moveCursor(uint8 row , uint8 col)
{
	uint8 lcd_memory_address=0x00;
	switch(row)
	{
	case 0:
		lcd_memory_address=col+0x00;
		break;
	case 1:
		lcd_memory_address=col+0x40;
		break;
	case 2: /*for 4 line LCD*/
		lcd_memory_address=col+0x10;
		break;
	case 3:
		lcd_memory_address=col+0x50;
		break;
	}

	LCD_sendCommand(lcd_memory_address | 0x80);
}

void LCD_integerToString(uint8 num)
{
	char numInAsci[16];
	itoa(num,numInAsci,10);
	LCD_writeString(numInAsci);
}

void LCD_clearScreen()
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}





