# makfile configuration

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: prepong.elf 

#additional rules for files

prepong.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o led3.o switches3.o buzzer3.o main.o pongstartscreen.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: prepong.elf
	mspdebug rf2500 "prog button.elf"

clean:
	rm -f *.o *.elf
