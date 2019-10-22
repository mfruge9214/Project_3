/*
 * File: flash.c
 * Description: This file handles the LED functionality on the KL25Z
 * Authors: Mike Fruge and Mark Hinkle
 */


#include "flash.h"
#include "logger.h"

void initLEDs()
{
#ifdef BOARD
	/* Wanna see if this works */
	/* Initialize LEDS to on */
	LED_RED_INIT(LED_ON);
	LED_BLUE_INIT(LED_ON);
	LED_GREEN_INIT(LED_ON);

	/* Turn LEDs off */

	LED_RED_OFF();
	LED_BLUE_OFF();
	LED_GREEN_OFF();

#endif
}


void RedLEDOn()
{
#ifdef BOARD
	LED_RED_ON();
	LED_GREEN_OFF();
	LED_BLUE_OFF();
#endif

#ifdef PC
	logString("Red LED On");
#endif
}

void BlueLEDOn()
{
#ifdef BOARD
	LED_RED_OFF();
	LED_GREEN_OFF();
	LED_BLUE_ON();
#endif

#ifdef PC
	logString("Blue LED On");
#endif
}

void GreenLEDOn()
{
#ifdef BOARD
	LED_RED_OFF();
	LED_GREEN_ON();
	LED_BLUE_OFF();
#endif

#ifdef PC
	logString("Green LED On");
#endif
}


/* BlinkLED: Executes 1 On, delay, Off, delay */
void blinkLED(enum Color color, uint32_t time_on, uint32_t time_off)
{
#ifdef BOARD
	/* Turn on desired LED */
	switch(color)
	{
	case RED:
		LED_RED_ON();
		break;
	case BLUE:
		LED_BLUE_ON();
		break;
	case GREEN:
		LED_GREEN_ON();
		break;
	}
#endif

#ifdef PC
	switch(color)
		{
		case RED:
			printf("RED LED ON\n");
			break;
		case BLUE:
			printf("BLUE LED ON\n");
			break;
		case GREEN:
			printf("GREEN LED ON\n");
			break;
		}
#endif


#ifdef BOARD
	/* Turn off desired LED */
	switch(color)
	{
	case RED:
		LED_RED_OFF();
		break;
	case BLUE:
		LED_BLUE_OFF();
		break;
	case GREEN:
		LED_GREEN_OFF();
		break;
	}
#endif

#ifdef PC
	switch(color)
		{
		case RED:
			printf("RED LED OFF\n");
			break;
		case BLUE:
			printf("BLUE LED OFF\n");
			break;
		case GREEN:
			printf("GREEN LED OFF\n");
			break;
		}
#endif
}

