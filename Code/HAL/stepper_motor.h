/******************************************************************************
 *
 * Module: stepper motor
 *
 * File Name: steeper_motor.h
 *
 * Description: Header file for the stepper motor
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef STEPPER_H_
#define STEPPER_H_

#include "std_types.h"

/*
 * stepper motor port and pin definition
 */
#define STEPPER_PORT PORTD_ID
#define STEPPER_FIRST_PIN PIN4_ID
#define STEPPER_SECOND_PIN PIN5_ID
#define STEPPER_THIRD_PIN PIN6_ID
#define STEPPER_FOURTH_PIN PIN7_ID

/*
 * data type to represent stepper motor direction
 */
typedef enum {
	RIGHT, LEFT
} stepperMotor_Direction;

/*
 * Description :
 * Functional responsible for Initialize the stepper motor by:
 * set the required pin directions and output some initial value
 */
void stepperMotor_Init(void);

/*
 * Description :
 * Functional responsible for rotating the stepper motor by:
 * rotate the stepper motor by the given degree in the given direction
 */
void stepperMotor_rotate(uint8 degree, stepperMotor_Direction direction);

#endif
