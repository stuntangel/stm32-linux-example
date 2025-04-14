# Makefile for common commands

# Target name
TARGET = basename "$PWD"

# Default target
all: link compile elf_to_bin flash flash

# Build target: Compile the program
link: @echo "linking program files for building"
      cd ./Debug
      arm-none-eabi-gcc "../Core/Src/main.c" -mcpu=cortex-m4 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4A6xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"Core/Src/main.o" -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "Core/Src/main.o"
      cd ../

compile: @echo "compiling to .elf file"
	cd ./Debug
	DIR = "$PWD/.."
	TAR_DIR = basename $(DIR)
	arm-none-eabi-gcc -o "$(TAR_DIR).elf" @"objects.list" -Wl,--start-group -Wl,--end-group -mcpu=cortex-m4 -T"$(DIR)/STM32L4A6ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="$(TAR_DIR).map" -Wl,--gc-sections -static -mfpu=fpv4- sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	cd ../

elf_to_bin:
	cd ./Debug
	arm-none-eabi-objcopy -O binary $(TARGET).elf "$(TARGET).bin"
	cd ../
# Flash target: Simulate flashing the program (for example purposes)
flash:
	@echo "Flashing to device..."
	st-flash --reset write ./Debug/$(TARGET).bin 0x08000000

# Rename target: Rename the executable (useful for versioning, etc.), defaults to basename of directory
rename:
	@echo "Renaming to $(TARGET)"
	mv stm32_demo.ioc $(TARGET).ioc
	mv 'stm32_demo Debug.launch' '$(TARGET) Debug.launch'
        mv ./Debug/stm32_demo.bin ./Debug/$(TARGET).bin
	mv ./Debug/stm32_demo.elf ./Debug/$(TARGET).elf
	mv ./Debug/stm32_demo.map ./Debug/$(TARGET).map
	mv ./Debug/stm32_demo.list ./Debug/$(TARGET).list

