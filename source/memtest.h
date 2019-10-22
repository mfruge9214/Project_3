/*
 * File: memtest.h
 * Description: This file defines macros and function prototypes for the memory functions
 * Authors: Mike Fruge and Mark Hinkle
 */

#include <stdint.h>
#include <stddef.h>
#include "pattern.h"


/* Definitions */

#define MEM_ALLOCATION_LIMIT	512
#define NULL_PTR                0x00000000UL

/* Structs */

typedef enum
{
	SUCCESS      =  0,
	INVALID_LOC  = -1,
	INVALID_LEN  = -2,
	FAILURE      = -3
} mem_status;

typedef struct
{
	uint32_t * blockptr;
	size_t length;
} mem_block;


/* Function Declarations */

/***********************************************
 * @brief	Allocate specified block of memory
 *
 * @param[in] len	Amount of bytes to allocate
 *
 * @returns Pointer to allocated block of memory
 ***********************************************/
uint32_t* allocateWords(size_t len);

/***********************************************
 * @brief	Free previously allocated block of memory
 *
 * @param[in] src	Base address of memory block
 *
 ***********************************************/
void freeWords(uint32_t* src);

/***********************************************
 * @brief	Read a segment of memory
 *
 * @param[in] loc	Base address to read memory from
 *
 * @param[in] len	Amount of bytes to read
 *
 * @param[out] ret  Contents of memory specified by inputs
 *
 * @returns SUCCESS or FAILURE
 ***********************************************/
mem_status displayMemory(uint32_t* loc, size_t len, uint8_t * ret);

/***********************************************
 * @brief	Write to an allocated byte of memory
 *
 * @param[in] loc	Address to write
 *
 * @param[in] value	Value to write the memory address with
 *
 * @returns SUCCESS or FAIL
 ***********************************************/
mem_status writeMemory(uint32_t* loc, uint8_t value);

/***********************************************
 * @brief	Invert an allocated block of memory
 *
 * @param[in] loc	Memory address to access
 *
 * @param[in] len	How many bytes to invert
 *
 * @returns SUCCESS or FAIL
 ***********************************************/
mem_status invertBlock(uint32_t* loc, size_t len);

/***********************************************
 * @brief	Generates a pseudo-random pattern and writes to a specified block of memory
 *
 * @param[in] loc	Address to write
 *
 * @param[in] len	Number of bytes to generate
 *
 * @param[in] seed	Value used by pattern generator to create the pattern
 *
 * @returns SUCCESS or FAIL
 ***********************************************/
mem_status writePattern(uint32_t* loc, size_t len, uint8_t seed);

/***********************************************
 * @brief	Verifies pattern at address in memory by generating pattern from seed, creating a
 * 			Byte array, and comparing the byte array to the contents of memory
 *
 * @param[in] loc	Address to compare pattern to
 *
 * @param[in] len	Number of bytes to generate
 *
 * @param[in] seed	Value used by pattern generator to create the pattern
 *
 * @param[out] ret  List of memory addresses where memory does not match
 *
 * @returns -1 if FAIL else returns number of memory discrepancies
 ***********************************************/
int8_t verifyPattern(uint32_t* loc, size_t len, int8_t seed, uint32_t ** ret);

/***********************************************
 * @brief	Calculates fully addressable memory location from an offset and a known base location
 *
 * @param[in] len	Offset from known memory location
 *
 * @returns Fully addressable memory location
 ***********************************************/
uint32_t* getAddress(uint32_t* loc, uint32_t offset);
