
CPU 		= msp430g2553
CFLAGS 		= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

CC 		= msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu=${CPU} -c

all: main.elf

main.elf: ${COMMON_OBJECTS} main.o wdt_handler.o led.o switches.o buzzer.o interrupt_handler.o State_Machine.o state_advance.s buzzer_advance.s 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
