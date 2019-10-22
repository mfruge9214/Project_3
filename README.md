# Project_3
 PES
 Project 3
 README
 _______________________________________________

Team Members: Mike Fruge and Mark Hinkle

Repo Description:
 This repository contains all of the project requirements for Project 3 of PES. 
 The most significant module is the project itself, containing the following source files: (main.c, main.h, logger.c, logger.h, memtest.c, memtest.h, flash.c, flash.h, pattern.c, and pattern.h). In addition to these sources files is a custom MakeFile that allows the user to select between building an executable for the PC or for the Freedom Development Board. The remaining files in the project are made by the developers at NXP.
 This repo also contains UML diagrams outlining the Activity and Sequence of our program.

 
 Observations:
  The most significant challenge was understanding the allocation and access to memory used in the memtests. Several of the function prototpes were needed to be rewritten in order to achieve the desired functionality. The following functions were changed:
  displayMemory - instead of returning an array of data, this array is defined in main and passed by reference. Returns error code instead
  verifyPattern - instead of returning an array of addresses, this array is defined in main and passed by references
  getAddress - this function has an additional input which is the initial address before the offset
  In addition to these obstacles we also faced issues with itegrating the LEDs; however, this was a minor fix.
  
  Installation/Execution Notes:
   There are two build targets: PC and KL25Z (which is used when flashing code to the Freedom Board). The PC build generates an executable called MyMakeProject.exe that is placed into the debug folder of the project. This can be ran by calling it from the terminal. The KL25Z build generates an executable called MyMakeProject.axf that can be loaded onto the board using the debugger. Logging can be truned on and off using the functions logEnable() and logDisable() in main.
