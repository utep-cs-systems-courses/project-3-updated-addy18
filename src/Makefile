CPU	= msp430g2553
CFLAGS 	= -mmcu=${CPU} -Os -I../h
LDFLAGS	= -L../lib -L/opt/ti/msp430_gcc/include

CC	= msp430-elf-gcc
AS	= msp430-elf-gcc -mmcu=${CPU} -c

all: toymain.elf

toymain.elf: ${COMMON_OBJECTS} toymain.o wdt_handler.o buzzer.o led.o interrupt_handler.o switches.o statemachine.o state_advance.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: toymain.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
