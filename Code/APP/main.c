/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: source file for the application
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#include "lcd.h"
#include "dc_motor.h"
#include "stepper_motor.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>

int main(void) {

	/*
	 * array the store the received frame
	 */
	uint8 frame[100];

	/*
	 * variable to store the DC motor speed
	 */
	uint8 DCMotor_speed = 100;

	/*
	 * variable to store the DC motor direction
	 */
	DcMotor_State DCMotor_direction = CLOCKWISE;

	/*
	 * variable to store the stepper motor angle
	 */
	uint8 stepperMotor_angle = 0;

	/*
	 * variable to store the stepper motor direction
	 */
	stepperMotor_Direction stepperMotor_direction = RIGHT;

	/*
	 * string used to display the DC motor speed and
	 * the stepper motor angle on LCD
	 */
	uint8 int_string[5];

	/*
	 * initialize the LCD module
	 */
	LCD_init();

	/*
	 * display speed and direction strings
	 */
	LCD_moveCursor(0, 0);
	LCD_displayString("Speed : ");

	LCD_moveCursor(1, 0);
	LCD_displayString("Direction : ");

	/*
	 * initialize the DC motor
	 */
	DcMotor_init();
	DcMotor_rotate(DCMotor_direction, DCMotor_speed);

	/*
	 * initialize the stepper motor
	 */
	stepperMotor_Init();
	stepperMotor_rotate(stepperMotor_angle, stepperMotor_direction);

	/*
	 * initialize the UART module
	 */
	UART_ConfigType config = { EIGHT_BIT, EVEN_PARITY, ONE_BIT, 9600 };
	UART_init(&config);

	while (1) {

		/*
		 * convert the DC motor speed to string and
		 * display it on the LCD
		 */
		itoa(DCMotor_speed, int_string, 10);
		LCD_moveCursor(0, 8);
		LCD_displayString(int_string);
		if (DCMotor_speed != 100) {
			LCD_displayCharacter(' ');
		}

		/*
		 * display the stepper motor direction on the LCD
		 */
		LCD_moveCursor(1, 12);
		if (stepperMotor_direction == LEFT) {
			LCD_displayCharacter('-');
		} else {
			LCD_displayCharacter('+');
		}

		/*
		 * convert the stepper motor angle to string and
		 * display it on the LCD
		 */
		itoa(stepperMotor_angle, int_string, 10);
		LCD_displayString(int_string);

		/*
		 * stay here waiting for a frame
		 */
		UART_receiveString(frame);
		UART_sendString(frame);

		/*
		 * the next code to validate the frame
		 */

		/*
		 * first, check the length of the frame
		 */
		if (strlen(frame) != 7) {

			UART_sendString("Invalid Frame");
			continue;
		}

		/*
		 * second, check that the speed of the DC motor is correct
		 */
		if (frame[0] != '1' && frame[0] != '0') {
			UART_sendString("Invalid Frame");
			continue;
		}

		if (frame[1] < '0' || frame[1] > '9') {
			UART_sendString("Invalid Frame");
			continue;
		}

		if (frame[2] < '0' || frame[2] > '9') {
			UART_sendString("Invalid Frame");
			continue;
		}

		/*
		 * third, check the DC motor direction
		 */
		if (frame[3] != 'F' && frame[3] != 'B') {
			UART_sendString("Invalid Frame");
			continue;
		}

		/*
		 * fourth, check the angle of stepper motor
		 */
		if (frame[4] < '0' || frame[4] > '4') {
			UART_sendString("Invalid Frame");
			continue;
		}

		if (frame[5] < '0' || frame[5] > '9') {
			UART_sendString("Invalid Frame");
			continue;
		}

		if (frame[4] == '4' && frame[5] > '5') {
			UART_sendString("Invalid Frame");
			continue;
		}

		/*
		 * fifth, check the direction of stepper motor
		 */
		if (frame[6] != 'L' && frame[6] != 'R') {
			UART_sendString("Invalid Frame");
			continue;
		}

		/*
		 * here we are sure that the frame is correct
		 */

		/*
		 * extract the DC motor speed from the frame
		 */
		DCMotor_speed = 0;
		for (uint8 i = 0; i < 3; i++) {
			DCMotor_speed *= 10;
			DCMotor_speed += (frame[i] - '0');
		}

		/*
		 * extract the DC motor direction from the frame
		 */
		if (frame[3] == 'B') {
			DCMotor_direction = CLOCKWISE;
		} else {
			DCMotor_direction = ANTICLOCKWISE;
		}

		/*
		 * extract the stepper motor angle from the frame
		 */
		stepperMotor_angle = 0;
		for (uint8 i = 4; i < 6; i++) {
			stepperMotor_angle *= 10;
			stepperMotor_angle += (frame[i] - '0');
		}

		/*
		 * extract the stepper motor direction from the frame
		 */
		if (frame[6] == 'L') {
			stepperMotor_direction = LEFT;
		} else {
			stepperMotor_direction = RIGHT;
		}

		/*
		 * rotate the DC motor and the stepper motor with the
		 * specified speed and directions
		 */
		DcMotor_rotate(DCMotor_direction, DCMotor_speed);
		stepperMotor_rotate(stepperMotor_angle, stepperMotor_direction);

	} /* end of while(1) loop */

	return 0;
}
