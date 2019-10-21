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

    printf("FREEDOMBOARD RUN\n\r");
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
    logInit();
    logEnable();
    logString(TestMsg);


    /* Allocate memory */
    block1.length = LEN;
    block1.blockptr = allocateWords(block1.length * sizeof(uint32_t));
    int i=0;
    uint32_t* temp = block1.blockptr;

//    for(i=0; i<block1.length; i++)
//    {
//    	writeMemory(temp, 0);
//    	printf("Wrote address 0x%p\n\r", temp);
//    	temp++;
//    }

    /* Check that memory was allocated */
    if(block1.blockptr != NULL)
    	printf("Memory Allocated\n\r");

    /* Write pattern to memory */
    result = writePattern(block1.blockptr, block1.length, seed);
    if(result != SUCCESS)
    {
    	printf("Write Pattern Error\n\r");
        freeWords(block1.blockptr);
        printf("Memory Freed\n\r");
        while(1);
    }
    printf("\nPattern Written Successfully!\n\r");

    /* Display memory contents */

    logData(block1.blockptr, 16);
    printf("Pattern Fully Displayed\n\r");


    /* Free allocated Block */
    freeWords(block1.blockptr);
    printf("\nMemory Freed\n\r");
}

