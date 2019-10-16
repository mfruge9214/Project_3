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

#ifdef BOARD
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#endif




int main(void) {

#if defined(BOARD)
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    /* Initialize LEDs */
    initLEDs();

    printf("FREEDOMBOARD RUN\n");
#endif

#ifdef PC_RUN
    printf("PC RUN\n");
#endif

    /* Variable Declarations */
    mem_block allocatedBlock1;
//    mem_block allocatedBlock2;
    uint8_t RandomNums[LEN];
    mem_status result;

    /* Allocate memory */
    allocatedBlock1.length = LEN;
    allocatedBlock1.blockptr = allocateWords(allocatedBlock1.length);
    if(allocatedBlock1.blockptr)
    {
    	printf("Memory Allocated\n");
    }

    /* Create and return the pattern */
    createPattern(LEN, 45, RandomNums);

    int i;
    for(i=0; i<LEN; i++)
    {
    	printf("Value: %d		Index: %d\n", RandomNums[i], i);
    }

    /* Write the pattern to memory */

    result = writeMemory(allocatedBlock1.blockptr, RandomNums[0]);
    if(!result)
    {
    	printf("Contents of memory verified\n");
    }

    /* Free allocated Block */
    freeWords(allocatedBlock1.blockptr);
    if(!allocatedBlock1.blockptr)
    {
    	printf("Memory Freed\n");
    }

}

