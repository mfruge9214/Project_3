#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Create Logging Structures */
/* Created in preparation for later assignments */

typedef enum ModuleID
{
	INIT,
	MAIN,
	MEMORY_TEST,
	LED_CONTROL,
}ModuleID;

typedef enum Priority_Lvl
{
	FATAL = 0,
	WARNING = 1,
	NOTICE = 2
}Priority_Lvl;





/***********************************************
 *
 * @brief	Initialize the global logger to its default state (disabled, WARNING, default buffer)
 *
 ***********************************************/
void logInit();

/***********************************************
 *
 * @brief	Enable Logger for printouts
 *
 ***********************************************/
void logEnable();

/***********************************************
 * @brief	Disable logger activity
 ***********************************************/
void logDisable();

/***********************************************
 * @brief	Check status of logger
 *
 * @return true if logger is enabled, false if not
 *
 ***********************************************/
bool logStatus();

/***********************************************
 * @brief	Prints out the address and values read from memory
 *
 * @param[in] loc	Pointer to base address to read from memory
 *
 * @param[in] len	Number of words to read from memory
 ***********************************************/
void logData(uint32_t* loc, size_t len);

/***********************************************
 * @brief	Read a segment of memory
 *
 * @param[in] loc	Base address to read memory from
 *
 * @param[in] len	Amount of bytes to read
 *
 * @returns Contents of memory location specified
 ***********************************************/
void logString(char* message);

/***********************************************
 * @brief	Read a segment of memory
 *
 * @param[in] loc	Base address to read memory from
 *
 * @param[in] len	Amount of bytes to read
 *
 * @returns Contents of memory location specified
 ***********************************************/
void logInteger();
