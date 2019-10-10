/*
 * main.c
 *
 *  Created on: 09/28/19
 *      Author:
 */
#include "main.h"
#include "flash.h"
#include "memtest.h"
#include "pattern.h"
#include "logger.h"

#if defined(FB_RUN) || defined(FB_DEBUG)
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#endif

#if defined(PC_RUN) || defined(PC_DEBUG)
#include <stdio.h>
#endif



int main(void) {

#if defined(FB_RUN)  || defined(FB_DEBUG)
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    /* Initialize LEDs */
    initLEDs();

    PRINTF("FREEDOMBOARD RUN\n");
#endif

#ifdef PC_RUN
    printf("PC RUN\n");
#endif


uint8_t* value;
value = createPattern(8, 8);
if(value)
{

}
//    uint8_t cycles = 0;
//    uint32_t time_on, time_off;
//    uint8_t lookup_idx, num_blinks;
//    num_blinks = 0;
//    enum Color color = RED;
//
//    /* Cycles through table 10 times */
//    while(cycles < CYCLES_THRU_TABLE)
//    {
//    	/* Controls the Flashing */
//    	for(lookup_idx = 0; lookup_idx < TABLE_ELEMENTS; lookup_idx += 2)
//    	{
//    		time_on = timing_lookup[lookup_idx];
//    		time_off = timing_lookup[lookup_idx+1];
//    		blinkLED(color, time_on, time_off);
//    		num_blinks++;
//    		/* Time to switch colors */
//    		if(num_blinks % 3 == 0)
//    		{
//    			if(color == RED) color = GREEN;
//    			else if(color == GREEN) color = BLUE;
//    			else if(color == BLUE) color = RED;
//    		}
//
//    	}
//    	cycles++;
//    }


}

