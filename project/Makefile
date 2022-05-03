# makfile configuration
COMMON_OBJECTS		= buzzer.o draw_shapes.o p2_interrupt_handler.o stateMachine.o drawing.o switches.o wdtInterruptHandler.o
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: demo.elf demo_s.elf

#additional rules for files
demo.elf: ${COMMON_OBJECTS} demo.o play.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

demo_s.elf: ${COMMON_OBJECTS} demo.o play_s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: demo.elf
	msp430loader.sh $^

load_s: demo_s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *.c~ *.h~ *.s~

play.o: play.c

play_s.o: play_s.s
