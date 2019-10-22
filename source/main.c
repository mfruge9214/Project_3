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
    uint8_t i = 0;
    int8_t mem_errors = 0;

    /* Logger Test*/
    char TestMsg[] = "This is a logger test\n";
    logInit();
    logEnable();
    logString(TestMsg);


    /* Allocate memory */
    block1.length = LEN;
    block1.blockptr = allocateWords(block1.length * sizeof(uint32_t));

    /* Check that memory was allocated */
    if(block1.blockptr != NULL)
    	printf("Memory Allocated at 0x%p\n\r", block1.blockptr);

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
    uint8_t mem_vals[block1.length];
    displayMemory(block1.blockptr, block1.length, mem_vals);
    for(i = 0; i < block1.length; i++)
    {
    	printf("Byte %d = 0x%X\n", i, mem_vals[i]);
    }
    printf("\n");

    /* Verify Pattern - Should Pass */
    uint32_t * mem_error_addr[block1.length];
    mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
    if(mem_errors == -1)
    {
    	//log error
    }
    else
    {
		for(i = 0; i < mem_errors; i++)
		{
			printf("Memory Discrepancy at 0x%p\n", mem_error_addr[i]);
		}
		printf("Pattern Verification Complete\n\n");
    }

    /* Calculate Offsets and Write New Value */
    uint32_t * offset_addr = getAddress(block1.blockptr, OFFSET_A);
    printf("Offset Address 1 = 0x%p\n", offset_addr);
    writeMemory(offset_addr, NEWVAL1);
    offset_addr = getAddress(block1.blockptr, OFFSET_A + 1);
    printf("Offset Address 2 = 0x%p\n", offset_addr);
    writeMemory(offset_addr, NEWVAL2);
    printf("Rewrote Bytes %u & %u with 0x%X%X\n\n", OFFSET_A, (OFFSET_A + 1), NEWVAL1, NEWVAL2);

    /* Display memory contents */
    displayMemory(block1.blockptr, block1.length, mem_vals);
    for(i = 0; i < block1.length; i++)
    {
    	printf("Byte %d = 0x%X\n", i, mem_vals[i]);
    }
    printf("\n");

    /* Verify Pattern - Should Fail */
    mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
    if(mem_errors == -1)
    {
    	//log error
    }
    else
    {
		for(i = 0; i < mem_errors; i++)
		{
			printf("Memory Discrepancy at 0x%p\n", mem_error_addr[i]);
		}
		printf("Pattern Verification Complete\n\n");
    }

    /* Rewrite pattern to memory */
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
    displayMemory(block1.blockptr, block1.length, mem_vals);
    for(i = 0; i < block1.length; i++)
    {
    	printf("Byte %d = 0x%X\n", i, mem_vals[i]);
    }
    printf("\n");

    /* Verify Pattern - Should Pass */
    mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
    if(mem_errors == -1)
    {
    	//log error
    }
    else
    {
		for(i = 0; i < mem_errors; i++)
		{
			printf("Memory Discrepancy at 0x%p\n", mem_error_addr[i]);
		}
		printf("Pattern Verification Complete\n\n");
    }

    /* Calculate Address and Invert Bytes */
    offset_addr = getAddress(block1.blockptr, OFFSET_B);
    result = invertBlock(offset_addr, INVERT_LEN);
    if(result != SUCCESS)
    {
    	// log error
    }
    printf("Inverted %u bytes beginning at address 0x%p\n\n", INVERT_LEN, offset_addr);

    /* Display memory contents */
    displayMemory(offset_addr, INVERT_LEN, mem_vals);
    for(i = 0; i < INVERT_LEN; i++)
    {
    	printf("Byte %d = 0x%X\n", i + OFFSET_B, mem_vals[i]);
    }
    printf("\n");

    /* Verify Pattern - Should Fail */
    mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
    if(mem_errors == -1)
    {
    	//log error
    }
    else
    {
		for(i = 0; i < mem_errors; i++)
		{
			printf("Memory Discrepancy at 0x%p\n", mem_error_addr[i]);
		}
		printf("Pattern Verification Complete\n\n");
    }

    /* Re-Invert the Bytes */
    result = invertBlock(offset_addr, INVERT_LEN);
	if(result != SUCCESS)
	{
		// log error
	}
	printf("Inverted %u bytes beginning at address 0x%p\n\n", INVERT_LEN, offset_addr);

	/* Display memory contents */
	displayMemory(offset_addr, INVERT_LEN, mem_vals);
	for(i = 0; i < INVERT_LEN; i++)
	{
		printf("Byte %d = 0x%X\n", i + OFFSET_B, mem_vals[i]);
	}
	printf("\n");

	/* Verify Pattern - Should Pass */
	mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
	if(mem_errors == -1)
	{
		//log error
	}
	else
	{
		for(i = 0; i < mem_errors; i++)
		{
			printf("Memory Discrepancy at 0x%p\n", mem_error_addr[i]);
		}
		printf("Pattern Verification Complete\n\n");
	}

    logData(block1.blockptr, 16);
    printf("Pattern Fully Displayed\n\r");


    /* Free allocated Block */
    freeWords(block1.blockptr);
    printf("\nMemory Freed\n\r");
}

