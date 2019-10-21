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

#ifdef BOARD
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    /* Initialize LEDs */
    initLEDs();

    printf("FREEDOMBOARD RUN\n");
#endif

#ifdef PC
    printf("PC RUN\n");
#endif

    /* Variable Declarations */
    mem_block block1;
    mem_status result;
    uint8_t seed = 45;
//    uint32_t * val_ptr;
//    uint8_t temp;

    /* Logger Test*/
    char TestMsg[] = "This is a logger test\n";
    logEnable();
    logString(TestMsg);


    /* Allocate memory */
    block1.length = LEN;

    /* When I include this sizeof(), we dont segfault (for obvious reasons). When it is not included, there is a segfault after accessing index 15 */

    block1.blockptr = allocateWords(block1.length * sizeof(uint32_t));
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

    logData(block1.blockptr, 16);
    printf("Pattern Fully Displayed\n");


    /* Free allocated Block */
    freeWords(block1.blockptr);
    printf("\nMemory Freed\n");
}

