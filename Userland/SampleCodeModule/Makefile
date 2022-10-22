include ../Makefile.inc

# MODULE=0000-sampleCodeModule.bin
#SOURCES=$(wildcard [^_].c)
#OBJECTS=$(SOURCES:.c=.o)
#
#SOURCES_ASM=$(wildcard asm/*.asm)
#OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
#
#all: $(MODULE)
#
#$(MODULE): $(OBJECTS) $(OBJECTS_ASM)
#	$(LD) $(LDFLAGS) $(OBJECTS) $(OBJECTS_ASM) -o ../$(MODULE)
#
#%.o: %.c
#	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c -c $< -o $@
#
#%.o : %.asm
#	$(ASM) $(ASMFLAGS) $< -o $@
#
#clean:
#	rm -rf *.o
#
#.PHONY: all clean print
#

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print