# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:button.elf pong2.elf

#additional rules for files

button.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o led3.o switches3.o buzzer3.o buttonCode.o ../lib/libTimer.a  ${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
 
pong2.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o led3.o switches3.o buzzer3.o main.o pongstartscreen.o ../lib/libTimer.a ${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
  
    
load: button.elf
	mspdebug rf2500 "prog button.elf"
load2: pong2.elf
	mspdebug rf2500 "prog button.elf"

clean:
	rm -f libShape.a *.o *.elf

load: shapemotion.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf

