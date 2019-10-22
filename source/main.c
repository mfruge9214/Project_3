/*
 * File: main.c
 * Description: This file runs the desired program for PES Project 3
 * Authors: Mike Fruge and Mark Hinkle
 * Tools: GCC99 Library & GNU Toolchain
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
    int8_t mem_errors = 0;
    uint8_t mem_vals[LEN];
    uint32_t * mem_error_addr[LEN];

    /* Logger Test*/
    logInit();
    logEnable();

    /* Start Memory Tests */
    BlueLEDOn();

    /*** (1) Allocate memory ***/
    block1.length = LEN;
    block1.blockptr = allocateWords(block1.length * sizeof(uint32_t));
    if(block1.blockptr != NULL)
    {
    	logString("Memory Allocated");
    	GreenLEDOn();
    }
    else
    {
    	logString("Allocate Words Failed");
    	RedLEDOn();
		while(1);
    }


    /*** (2) Write pattern to memory ***/
    result = writePattern(block1.blockptr, block1.length, seed);
    if(result == SUCCESS)
    {
    	logString("Pattern Written Successfully\n");
    	GreenLEDOn();
    }
    else
    {
    	logString("Write Pattern Failed with Error:");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }


    /*** (3) Display memory contents ***/
    result = displayMemory(block1.blockptr, block1.length, mem_vals);
    if(result == SUCCESS)
    {
    	logString("Displaying Memory:");
    	GreenLEDOn();
    }
    else
    {
    	logString("Invalid Inputs to displayMemory: ");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }
	logData(block1.blockptr, block1.length);


    /*** (4) Verify Pattern - Should Pass ***/
    mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
    if(mem_errors == -1)
    {
    	logString("Invalid Inputs to verifyPattern\n");
    	RedLEDOn();
    }
    else if (mem_errors == 0)
    {
    	logString("Pattern Verified - No Errors\n");
    	GreenLEDOn();
    }
    else
    {
    	logString("\nNumber of Memory Discrepancies:");
    	logInteger(mem_errors);
    	logData(mem_error_addr[0], mem_errors);
		logString("Pattern Verification Complete\n");
		RedLEDOn();
    }


    /*** (5) Calculate Offsets and Write New Value ****/
    uint32_t * offset_addr = getAddress(block1.blockptr, OFFSET_A);
    result = writeMemory(offset_addr, NEWVAL1);
    if(result == SUCCESS) //continue
    {
    	logString("Rewrote byte 5 with 0xFF");
        offset_addr = getAddress(block1.blockptr, OFFSET_A + 1);
        result = writeMemory(offset_addr, NEWVAL2);
        if(result == SUCCESS)
        {
        	logString("Rewrote byte 6 with 0xEE");
        	GreenLEDOn();
        }
        else
        {
        	logString("Failed Writing Memory to Offset Address\n");
        	RedLEDOn();
        }
    }
    else
    {
    	logString("Failed Writing Memory to Offset Address\n");
    	RedLEDOn();
    }


    /*** (6) Display memory contents ***/
    result = displayMemory(block1.blockptr, block1.length, mem_vals);
    if(result == SUCCESS)
    {
    	logString("Displaying Memory:");
    	GreenLEDOn();
    }
    else
    {
    	logString("Invalid Inputs to displayMemory: ");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }
	logData(block1.blockptr, block1.length);


	/*** (7) Verify Pattern - Should Fail ***/
	mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
	if(mem_errors == -1)
	{
		logString("Invalid Inputs to verifyPattern\n");
		RedLEDOn();
	}
	else if (mem_errors == 0)
	{
		logString("Pattern Verified - No Errors\n");
		GreenLEDOn();
	}
	else
	{
    	logString("\nNumber of Memory Discrepancies:");
    	logInteger(mem_errors);
    	logData(mem_error_addr[0], mem_errors);
		logString("Pattern Verification Complete\n");
		RedLEDOn();
	}


    /*** (8) Rewrite pattern to memory ***/
    result = writePattern(block1.blockptr, block1.length, seed);
    if(result == SUCCESS)
    {
    	logString("Pattern Written Successfully\n");
    	GreenLEDOn();
    }
    else
    {
    	logString("Write Pattern Failed with Error:");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }


    /*** (9) Display memory contents ***/
    result = displayMemory(block1.blockptr, block1.length, mem_vals);
    if(result == SUCCESS)
    {
    	logString("Displaying Memory:");
    	GreenLEDOn();
    }
    else
    {
    	logString("Invalid Inputs to displayMemory: ");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }
	logData(block1.blockptr, block1.length);


    /*** (10) Verify Pattern - Should Pass ***/
    mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
    if(mem_errors == -1)
    {
    	logString("Invalid Inputs to verifyPattern\n");
    	RedLEDOn();
    }
    else if (mem_errors == 0)
    {
    	logString("Pattern Verified - No Errors\n");
    	GreenLEDOn();
    }
    else
    {
    	logString("\nNumber of Memory Discrepancies:");
    	logInteger(mem_errors);
    	logData(mem_error_addr[0], mem_errors);
		logString("Pattern Verification Complete\n");
		RedLEDOn();
    }


    /*** (11) Calculate Address and Invert Bytes ***/
    offset_addr = getAddress(block1.blockptr, OFFSET_B);
    result = invertBlock(offset_addr, INVERT_LEN);
    if(result == SUCCESS)
    {
    	logString("Inverted 4 Bytes Beginning at Byte 8\n");
    	GreenLEDOn();
    }
    else
    {
    	logString("Invert Block Failed\n");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }


    /*** (12) Display memory contents ***/
    result = displayMemory(block1.blockptr, block1.length, mem_vals);
    if(result == SUCCESS)
    {
    	logString("Displaying Memory:");
    	GreenLEDOn();
    }
    else
    {
    	logString("Invalid Inputs to displayMemory: ");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }
	logData(block1.blockptr, block1.length);


    /*** (13) Verify Pattern - Should Fail ***/
    mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
    if(mem_errors == -1)
    {
    	logString("Invalid Inputs to verifyPattern\n");
    	RedLEDOn();
    }
    else if (mem_errors == 0)
    {
    	logString("Pattern Verified - No Errors\n");
    	GreenLEDOn();;
    }
    else
    {
    	logString("\nNumber of Memory Discrepancies:");
    	logInteger(mem_errors);
    	logData(mem_error_addr[0], mem_errors);
		logString("Pattern Verification Complete\n");
		RedLEDOn();
    }


    /*** (14) Re-invert Bytes ***/
    result = invertBlock(offset_addr, INVERT_LEN);
    if(result == SUCCESS)
    {
    	logString("Inverted 4 Bytes Beginning at Byte 8\n");
    	GreenLEDOn();
    }
    else
    {
    	logString("Invert Block Failed\n");
    	logInteger((uint32_t)result);
    	RedLEDOn();
    }


    /*** (15) Display memory contents ***/
     result = displayMemory(block1.blockptr, block1.length, mem_vals);
     if(result == SUCCESS)
     {
     	logString("Displaying Memory:");
     	GreenLEDOn();
     }
     else
     {
     	logString("Invalid Inputs to displayMemory: ");
     	logInteger((uint32_t)result);
     	RedLEDOn();
     }
 	logData(block1.blockptr, block1.length);


     /*** (16) Verify Pattern - Should Fail ***/
     mem_errors = verifyPattern(block1.blockptr, block1.length, seed, mem_error_addr);
     if(mem_errors == -1)
     {
     	logString("Invalid Inputs to verifyPattern\n");
     	RedLEDOn();
     }
     else if (mem_errors == 0)
     {
     	logString("Pattern Verified - No Errors\n");
     	GreenLEDOn();
     }
     else
     {
     	logString("\nNumber of Memory Discrepancies:");
     	logInteger(mem_errors);
     	logData(mem_error_addr[0], mem_errors);
 		logString("Pattern Verification Complete\n");
 		RedLEDOn();
     }


    /*** (17) Free allocated Block ***/
    freeWords(block1.blockptr);
    logString("Memory Freed!!\n");
}

