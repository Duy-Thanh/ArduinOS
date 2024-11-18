# Microcontroller settings
MCU = atmega2560
F_CPU = 16000000UL

# Toolchain
CXX = avr-g++.exe
OBJCOPY = avr-objcopy.exe
SIZE = avr-size.exe

# Source files
SRCS = main.cpp \
       src/core/string.cpp \
       src/hal/uart_cmd.cpp \
       src/hal/gpio.cpp \
       src/hal/timer.cpp \
       src/hal/uart.cpp \
       src/hal/registers.cpp \
       src/kernel/scheduler.cpp \
       src/kernel/interrupt.cpp \
       src/drivers/led.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Compiler flags
CXXFLAGS = -mmcu=$(MCU) \
           -DF_CPU=$(F_CPU) \
           -Os \
           -Wall \
           -Wextra \
           -std=c++11 \
           -I. \
           -fno-exceptions \
           -fno-rtti \
           -ffunction-sections \
           -fdata-sections

# Linker flags
LDFLAGS = -mmcu=$(MCU) \
          -Wl,-Map=ArduinOS.map \
          -Wl,--gc-sections

all: clean ArduinOS.hex size

%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@ || (echo "Failed to compile $<" && exit 1)

ArduinOS.elf: $(OBJS)
	@echo "Linking $@..."
	@echo "Using objects: $(OBJS)"
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) || (echo "Failed to link $@" && exit 1)

ArduinOS.hex: ArduinOS.elf
	@echo "Creating $@..."
	$(OBJCOPY) -O ihex -R .eeprom $< $@

size: ArduinOS.elf
	@echo "Size information:"
	$(SIZE) --format=avr --mcu=$(MCU) $<
	@echo "Detailed section sizes:"
	$(SIZE) -A $<

clean:
	@echo "Cleaning..."
	rm -f ArduinOS.hex ArduinOS.elf $(OBJS) ArduinOS.map

flash: ArduinOS.hex
	avrdude.exe -v -p $(MCU) -c wiring -P COM1 -b 115200 -D -U flash:w:$<:i

.PHONY: all clean flash