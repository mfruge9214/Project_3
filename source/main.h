/*
 * main.h
 *
 *  Created on: 22.07.2017
 *      Author: Erich Styger Local
 */

#include <stdint.h>

#define CYCLES_THRU_TABLE	10
#define TABLE_ELEMENTS		20

#ifdef BOARD
#define printf	PRINTF
#endif

#define LEN		16

static const uint32_t timing_lookup[TABLE_ELEMENTS] =
{
		3000,1000,2000,600,1000,400,
		1000,200,500,100,500,100,
		500,100,1000,200,1000,400,
		2000,600
};


