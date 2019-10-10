# Working Makefile
############################
# Command for removing files
RM := rm -rf
 -include "C:\MinGW\bin" 
 
############################
# Binary/exectable to build
EXE := \
  ./debug/MyMakeProject.axf
  
PC_EXE := \
	./debug/MyMakeProject.exe

############################
# List of object files
OBJS := \
  ./debug/main.o \
  ./debug/startup_MKL25Z4.o \
  ./debug/system_MKL25Z4.o	\
  ./debug/board.o		\
  ./debug/clock_config.o \
  ./debug/peripherals.o	\
  ./debug/pin_mux.o	\
  ./debug/fsl_clock.o \
  ./debug/fsl_common.o \
  ./debug/fsl_flash.o	\
  ./debug/fsl_gpio.o	\
  ./debug/fsl_lpsci.o	\
  ./debug/fsl_smc.o		\
  ./debug/fsl_uart.o	\
  ./debug/fsl_debug_console.o \
  ./debug/flash.o		\
  ./debug/memtest.o	\
  ./debug/logger.o	\
  ./debug/pattern.o
  
  
#############################
PC_OBJS := ./debug/main.o \
		./debug/flash.o	\
  		./debug/memtest.o	\
  		./debug/logger.o	\
  		./debug/pattern.o		
		
############################
# List of dependency files
C_DEPS = \
  ./debug/main.d \
  ./debug/startup_MKL25Z4.d \
  ./debug/system_MKL25Z4.d	\
  ./debug/board.d		\
  ./debug/clock_config.d \
  ./debug/peripherals.d	\
  ./debug/pin_mux.d	\
  ./debug/fsl_clock.d \
  ./debug/fsl_common.d \
  ./debug/fsl_flash.d	\
  ./debug/fsl_gpio.d	\
  ./debug/fsl_lpsci.d	\
  ./debug/fsl_smc.d		\
  ./debug/fsl_uart.d	\
  ./debug/flash.d		\
  ./debug/fsl_debug_console.d	\
  ./debug/memtest.d	\
  ./debug/logger.d	\
  ./debug/pattern.d
  
  
  
 
  
 ###########################
 # Included directories
 
 INCLUDES := \
 		-I"CMSIS" \
 		-I"board" \
 		-I"drivers" \
 		-I"source" \
 		-I"utilities" \
 		
 		
PC_INCLUDES := \
		-I"source"




############################
# Include generated dependcy files (only if not clean target)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif


############################
# Specify the options depending on target
ifeq ($(MAKECMDGOALS), all)
	PLATFORM := FB
	CC := arm-none-eabi-gcc
	CC_OPTIONS := -c -std=gnu99 -O0 -g -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m0plus -mthumb -DCPU_MKL25Z128VLK4 -D__USE_CMSIS $(INCLUDES)
	CC_OPTIONS += -DFB_RUN -DSDK_DEBUGCONSOLE
	LL := arm-none-eabi-gcc
	LL_OPTIONS := -nostdlib -Xlinker -Map="debug/MyMakeProject.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T linkerfile.ld -o $(EXE)
endif
	
	
ifeq ($(MAKECMDGOALS), fb_run)
	PLATFORM := FB
	CC := arm-none-eabi-gcc
	CC_OPTIONS := -c -std=gnu99 -O0 -g -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m0plus -mthumb -DCPU_MKL25Z128VLK4 -D__USE_CMSIS $(INCLUDES)
	CC_OPTIONS += -DFB_RUN -DSDK_DEBUGCONSOLE
	LL := arm-none-eabi-gcc
	LL_OPTIONS := -nostdlib -Xlinker -Map="debug/MyMakeProject.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T linkerfile.ld -o $(EXE)
endif

ifeq ($(MAKECMDGOALS), pc_run)
	PLATFORM := PC
	CC := gcc
	CC_OPTIONS := -Wall -Werror $(PC_INCLUDES)
	CC_OPTIONS += -DPC_RUN
	LL := gcc
endif

ifeq ($(MAKECMDGOALS), fb_debug)
	PLATFORM := FB
	CC := arm-none-eabi-gcc
	CC_OPTIONS := -c -std=gnu99 -O0 -g -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m0plus -mthumb -DCPU_MKL25Z128VLK4 -D__USE_CMSIS $(INCLUDES)
	CC_OPTIONS += -DFB_DEBUG -DSDK_DEBUGCONSOLE
	LL := arm-none-eabi-gcc
	LL_OPTIONS := -nostdlib -Xlinker -Map="debug/MyMakeProject.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T linkerfile.ld -o $(EXE)
endif

ifeq ($(MAKECMDGOALS), pc_debug)
	PLATFORM := PC
	CC := gcc
	CC_OPTIONS := -Wall -Werror $(PC_INCLUDES)
	CC_OPTIONS += -DPC_DEBUG
	LL := gcc
endif

# Main Targets
all: $(EXE)
	@echo "*** finished building ***"

fb_run: $(EXE)
	@echo "*** FINISHED BUILDING FB_RUN ***"
	
pc_run: $(PC_EXE)
	@echo "*** FINISHED BUILDING PC_RUN ***"
	
fb_debug: $(EXE)
	@echo "*** FINISHED BUILDING FB_DEBUG ***"
	
pc_debug: $(PC_EXE)
	@echo "*** FINISHED BUILDING PC_DEBUG ***"
	
############################
# Clean target
clean:
	-$(RM) $(EXECUTABLES) $(OBJS) $(EXE)
	-$(RM) ./debug/*.map
	-@echo ' '

############################
# FB compilation section

ifeq ($(PLATFORM), FB)
$(EXE): $(OBJS) $(USER_OBJS) linkerfile.ld
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(LL) $(LL_OPTIONS) $(OBJS) $(LIBS) $(INCLUDES)
	@echo 'Finished building target: $@'
	@echo ' '


############################
# Rule to build the files in the source folder

# Add files that are created here
./debug/main.o: ./source/main.c ./source/main.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/flash.o: ./source/flash.c ./source/flash.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/memtest.o: ./source/memtest.c ./source/memtest.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/logger.o: ./source/logger.c ./source/logger.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/pattern.o: ./source/pattern.c ./source/pattern.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
endif

PC_SCRS := \
		./source/main.c \
		./source/flash.c \
		./source/memtest.c	\
		./source/logger.c	\
		./source/pattern.c	\
###########################
# PC Compilation
ifeq ($(PLATFORM), PC)
$(PC_EXE):	$(PC_SCRS)
	$(CC) -o $(PC_EXE) $(CC_OPTIONS) $(PC_SCRS)
endif


# Do not add any files
###########################
###########################
# library files

./debug/system_MKL25Z4.o: ./CMSIS/system_MKL25Z4.c ./CMSIS/system_MKL25Z4.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


./debug/startup_MKL25Z4.o: ./CMSIS/startup_MKL25Z4.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
	
./debug/board.o: ./board/board.c ./board/board.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/clock_config.o: ./board/clock_config.c ./board/clock_config.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/peripherals.o: ./board/peripherals.c ./board/peripherals.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/pin_mux.o: ./board/pin_mux.c ./board/pin_mux.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
	
./debug/fsl_clock.o: ./drivers/fsl_clock.c ./drivers/fsl_clock.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/fsl_common.o: ./drivers/fsl_common.c ./drivers/fsl_common.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/fsl_flash.o: ./drivers/fsl_flash.c ./drivers/fsl_flash.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/fsl_gpio.o: ./drivers/fsl_gpio.c ./drivers/fsl_gpio.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/fsl_lpsci.o: ./drivers/fsl_lpsci.c ./drivers/fsl_lpsci.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/fsl_port.o: ./drivers/fsl_port.c ./drivers/fsl_port.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
./debug/fsl_smc.o: ./drivers/fsl_smc.c ./drivers/fsl_smc.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
	
./debug/fsl_uart.o: ./drivers/fsl_uart.c ./drivers/fsl_uart.h
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

./debug/fsl_debug_console.o: ./utilities/fsl_debug_console.c 
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '