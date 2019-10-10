#include "flash.h"



void initLEDs()
{
#if defined(FB_RUN)  || defined(FB_DEBUG)
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

/* BlinkLED: Executes 1 On, delay, Off, delay */
void blinkLED(enum Color color, uint32_t time_on, uint32_t time_off)
{
#if defined(FB_RUN)  || defined(FB_DEBUG)
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

#if defined(PC_RUN)  || defined(PC_DEBUG)
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


#if defined(FB_RUN)  || defined(FB_DEBUG)
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

#if defined(PC_RUN)  || defined(PC_DEBUG)
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

