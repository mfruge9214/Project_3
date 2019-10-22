/*
 * File: flash.c
 * Description: This file defines macros and function prototypes for LEDS
 * Authors: Mike Fruge and Mark Hinkle
 */

#include <stdint.h>
#include <stdio.h>


#ifdef BOARD
#include "board.h"

#define	RED_PORT	GPIOB
#define	RED_PIN		18U
#define GREEN_PORT	GPIOB
#define GREEN_PIN	19U
#define BLUE_PORT	GPIOD
#define BLUE_PIN	1U

#define LED_ON		0U
#define LED_OFF		1U
#endif

enum Color
{
	RED,
	GREEN,
	BLUE
};


/***********************************************
 *
 * @brief	Blinks the led of specified color for time on and time off
 *
 * @param[in] Color		Color to set the LED to when on
 *
 * @param[in] time_on	Amount of time to leave LED in ON state
 *
 * @param[in] time_off 	Amount of time to leave LED in OFF state
 *
 ***********************************************/
void blinkLED(enum Color color, uint32_t time_on, uint32_t time_off);

/***********************************************
 *
 * @brief	Set LED to RED and disable other colors
 *
 ***********************************************/
void RedLEDOn();

/***********************************************
 *
 * @brief	Set LED to Green and disable other colors
 *
 ***********************************************/
void GreenLEDOn();

/***********************************************
 *
 * @brief	Set LED to Green and disable other colors
 *
 ***********************************************/
void BlueLEDOn();

/***********************************************
 *
 * @brief	Initialize LEDs to off and route their pins
 *
 ***********************************************/
void initLEDs();

/***********************************************
 *
 * @brief	Delays for time ms
 *
 * @param[in] time	Approximate amount of milliseconds to delay for
 *
 ***********************************************/
void delay(uint32_t time);
