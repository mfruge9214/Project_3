/*
 * File: main.h
 * Description: This file defines macros and function prototypes for main
 * Authors: Mike Fruge and Mark Hinkle
 */

#include <stdint.h>

#define CYCLES_THRU_TABLE	10
#define TABLE_ELEMENTS		20


#define LEN			16

#define NEWVAL1     0xFF
#define NEWVAL2     0xEE
#define OFFSET_A 	5

#define INVERT_LEN  4
#define OFFSET_B   	8


static const uint32_t timing_lookup[TABLE_ELEMENTS] =
{
		3000,1000,2000,600,1000,400,
		1000,200,500,100,500,100,
		500,100,1000,200,1000,400,
		2000,600
};


