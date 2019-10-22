/*
 * File: logger.c
 * Description: This file handles the logger functionality for the program
 * Authors: Mike Fruge and Mark Hinkle
 */

#include "logger.h"

/* Private Variable */
static bool LogEnable;


void logInit()
{
	LogEnable = false;
}


void logEnable()
{
	if(LogEnable)
	{
		printf("Log already Enabled\n\r");
	}
	else
	{
		LogEnable = true;
		printf("Log Enabled\n\r");
	}

}


void logDisable()
{
	printf("Disabling Logger\n\r");
	if(LogEnable)
	{
		LogEnable = false;
	}
}


bool logStatus()
{
	return LogEnable;
}


void logData(uint32_t* loc, size_t len)
{

	if(!LogEnable)
	{
		return;
	}
	uint32_t* currLoc = loc;
	size_t i = 0;


	for(i=0; i<len; i++)
	{
		printf("Address: 0x%p		Value: 0x%02X \n\r", currLoc, *currLoc);
		currLoc++;
	}

}


void logString(char* message)
{
	if(!LogEnable)
	{
		return;
	}

	printf("%s\n\r", message);


}


void logInteger(uint32_t value)
{
	/* Ensure Logger Enabled */
	if(!LogEnable)
	{
		return;
	}

	printf("%d\n\r", value);

}


