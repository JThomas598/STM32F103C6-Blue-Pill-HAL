PROJECT_NAME := minimal

CFLAGS  := -g --specs=nosys.specs -Iinc -Wall -Werror -mcpu=cortex-m3  
LDFLAGS :=  -nostdlib -Tlink.ld
SOURCES := main.c rcc.c gpio.c 
OBJS    := objs/main.o objs/rcc.o objs/gpio.o

.PHONY: dump_elf
.PHONY: dump_bin
.PHONY: clean
.PHONY: flash

build: $(PROJECT_NAME).elf

$(PROJECT_NAME).elf: $(OBJS)
	arm-none-eabi-gcc $(CFLAGS) $(LDFLAGS) -o bin/$(PROJECT_NAME) $(OBJS)
	arm-none-eabi-objcopy -O binary bin/$(PROJECT_NAME) bin/$(PROJECT_NAME).bin

objs/%.o: src/%.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

dump_elf: $(PROJECT_NAME).elf
	arm-none-eabi-objdump --section-headers --syms $<

dump_bin: $(PROJECT_NAME).bin
	hexdump -vC $<

flash: $(PROJECT_NAME).elf
	sudo st-flash --reset write minimal.bin 0x08000000

clean:
	rm -rf objs/main.o objs/rcc.o $(PROJECT_NAME).*
