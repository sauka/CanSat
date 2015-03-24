###############################################################################
# Makefile for the project lcd_temperature
###############################################################################

## General Flags
PROJECT = lcd_temperature
MCU = atmega16
TARGET = lcd_temperature.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99          -lprintf_flt    -Wl,-u,vfprintf -lprintf_flt -lm      -DF_CPU=8000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=lcd_temperature.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Libraries
LIBS = -lprintf_flt -lscanf_flt 

## Objects that must be built in order to link
OBJECTS = main.o ds18b20.o adchelper.o usarthelper.o amhelper.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) lcd_temperature.hex lcd_temperature.eep lcd_temperature.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ds18b20.o: ../ds18b20.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

adchelper.o: ../adchelper.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usarthelper.o: ../usarthelper.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

amhelper.o: ../amhelper.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) lcd_temperature.elf dep/* lcd_temperature.hex lcd_temperature.eep lcd_temperature.lss lcd_temperature.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

