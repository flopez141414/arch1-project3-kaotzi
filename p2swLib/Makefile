all: libp2sw.a

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as -mmcu=${CPU} -c
AR              = msp430-elf-ar 

OBJECTS         = p2switches.o

libp2sw.a: $(OBJECTS)
	$(AR) crs $@ $^

$(OBJECTS): p2switches.h

install: libp2sw.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f *.a *.o *.elf

p2sw-demo.elf: p2sw-demo.o  tiltscreen.o wdt_handler.o libp2sw.a state.o
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^ -lLcd -lTimer -lShape -lCircle

load: p2sw-demo.elf
	mspdebug rf2500 "prog $^"

shapemotion.elf: shapemotion.o tiltscreen.o wdt_handler.o libp2sw.a 
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^ -lLcd -lTimer -lShape -lCircle

loadm: shapemotion.elf
	mspdebug rf2500 "prog $^"

