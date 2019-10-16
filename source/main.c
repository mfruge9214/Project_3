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
#include <stdio.h>


#if defined(FB_RUN) || defined(FB_DEBUG)
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#endif

#if defined(PC_RUN) || defined(PC_DEBUG)

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

    /* Variable Declarations */
    mem_block block1;
    mem_status result;
    uint8_t seed = 45;
    uint32_t * val_ptr;
    uint8_t temp;


    /* Allocate memory */
    block1.length = LEN;
    block1.blockptr = allocateWords(block1.length);
    if(block1.blockptr != NULL)
    	printf("Memory Allocated\n");

    /* Write pattern to memory */
    result = writePattern(block1.blockptr, block1.length, seed);
    if(result != SUCCESS)
    {
    	printf("Write Pattern Error\n");
        freeWords(block1.blockptr);
        printf("Memory Freed\n");
        while(1);
    }
    printf("\nPattern Written Successfully!\n");

    /* Display memory contents */
//    val_ptr = displayMemory(block1.blockptr, block1.length);
    val_ptr = block1.blockptr;
    for(uint8_t i = 0; i < block1.length; i++)
    {
    	temp = *val_ptr;
    	printf("Byte %u = %u\n",i,temp);
    	val_ptr++;
    }
    printf("Pattern Fully Displayed\n");

    /* Free allocated Block */
    freeWords(block1.blockptr);
    printf("\nMemory Freed\n");
}

