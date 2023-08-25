/******************************************************************************
 *
 * Module: stepper motor
 *
 * File Name: steeper_motor.c
 *
 * Description: source file for the stepper motor
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#include "stepper_motor.h"
#include "gpio.h"

/*
 * array to represent the stepper motor half step sequence
 */
static uint8 motor_steps[] = { 8, 9, 12, 4, 6, 1, 3, 2 };

/*
 * Description :
 * Functional responsible for Initialize the stepper motor by:
 * set the required pin directions and output some initial value
 */
void stepperMotor_Init(void) {

	GPIO_setupPinDirection(STEPPER_PORT, STEPPER_FIRST_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_PORT, STEPPER_SECOND_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_PORT, STEPPER_THIRD_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(STEPPER_PORT, STEPPER_FOURTH_PIN, PIN_OUTPUT);

	GPIO_writePin(STEPPER_PORT, STEPPER_FIRST_PIN, LOGIC_LOW);
	GPIO_writePin(STEPPER_PORT, STEPPER_SECOND_PIN, LOGIC_LOW);
	GPIO_writePin(STEPPER_PORT, STEPPER_THIRD_PIN, LOGIC_LOW);
	GPIO_writePin(STEPPER_PORT, STEPPER_FOURTH_PIN, LOGIC_LOW);
}

/*
 * Description :
 * Functional responsible for rotating the stepper motor by:
 * rotate the stepper motor by the given degree in the given direction
 */
void stepperMotor_rotate(uint8 degree, stepperMotor_Direction direction) {

	uint8 index = degree % 8;

	if (direction == RIGHT) {
		index = 8 - index;

		if (index == 8) {
			index = 0;
		}
	}

	GPIO_writePin(STEPPER_PORT, STEPPER_FIRST_PIN,
			(motor_steps[index] >> 0) & 0x01);
	GPIO_writePin(STEPPER_PORT, STEPPER_SECOND_PIN,
			(motor_steps[index] >> 1) & 0x01);
	GPIO_writePin(STEPPER_PORT, STEPPER_THIRD_PIN,
			(motor_steps[index] >> 2) & 0x01);
	GPIO_writePin(STEPPER_PORT, STEPPER_FOURTH_PIN,
			(motor_steps[index] >> 3) & 0x01);

}
