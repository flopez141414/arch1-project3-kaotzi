all: libShape.a shapedemo.elf shapedemo2.elf shapedemo3.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

OBJECTS         = shape.o region.o rect.o vec2.o layer.o rarrow.o diamond.o tilt.o

libShape.a: $(OBJECTS)
	$(AR) crs $@ $^

$(OBJECTS): shape.h

install: libShape.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f libShape.a *.o *.elf

shapedemo.elf: shapedemo.o libShape.a 
	$(CC) $(CFLAGS) ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@
shapedemoT.elf: shapedemot.o libShape.a 
	$(CC) $(CFLAGS) ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@
shapedemoI.elf: shapedemoi.o libShape.a 
	$(CC) $(CFLAGS) ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@
shapedemoL.elf: shapedemol.o libShape.a 
	$(CC) $(CFLAGS) ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@
shapedemoPong.elf: shapedemoPong.o libShape.a 
	$(CC) $(CFLAGS) ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@

shapedemo2.elf: shapedemo2.o libShape.a 
	$(CC) $(CFLAGS) ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@

shapedemo3.elf: shapedemo3.o libShape.a 
	$(CC) $(CFLAGS) ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@

load: shapedemo.elf
	mspdebug rf2500 "prog $^"

load2: shapedemo2.elf
	mspdebug rf2500 "prog $^"

load3: shapedemo3.elf
	mspdebug rf2500 "prog $^"
loadt: shapedemot.elf
	mspdebug rf2500 "prog $^"
loadi: shapedemoi.elf
	mspdebug rf2500 "prog $^"
loadl: shapedemol.elf
	mspdebug rf2500 "prog $^"
loadp: shapedemoPong.elf
	mspdebug rf2500 "prog $^"
