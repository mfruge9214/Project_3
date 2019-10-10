/*
 * File: flash.h
 * Description: LED binking API
 * Author: Mike Fruge
 */

#include <stdint.h>
#include <stdio.h>

#if defined(FB_RUN) || defined(FB_DEBUG)
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

void blinkLED(enum Color color, uint32_t time_on, uint32_t time_off);
void initLEDs();
void delay(uint32_t time);


