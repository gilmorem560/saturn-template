#
# SGL Makefile Template
#

CC = gcc
LD = ld
RM = deltree /Y
CONV = objcopy

SGLDIR = C:/Cygnus
SGLIDR = $(SGLDIR)/include
SGLLDR = $(SGLDIR)/lib

CCFLAGS = -O2 -m2 -g -c -I$(SGLIDR)
LDFLAGS = -T$(LDFILE) -Map $(MPFILE) -e ___Start

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)
LIBS = -lsgl

TARGET = main.coff
TARGET1 = main.bin
LDFILE = $(TARGET:.coff=.lnk)
MPFILE = $(TARGET:.coff=.map)
MAKEFILE = Makefile

all: $(TARGET) $(TARGET1)

$(TARGET): $(OBJS) $(MAKEFILE) $(LDFILE)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

$(TARGET1): $(OBJS) $(MAKEFILE)
	$(CONV) -O binary $(TARGET) $(TARGET1)

disc: $(TARGET1)
	vcdbuild vcd
	vcdmktoc vcd

$(LDFILE) : $(MAKEFILE)
	echo Making $(LDFILE)
	echo SECTIONS {			>  $@
	echo 	SLSTART 0x06004000 : {	>> $@
	echo 		___Start = .;	>> $@
	echo 		*(SLSTART)	>> $@
	echo 	}			>> $@
	echo }				>> $@

.SUFFIXES: .asm

.c.o:
	$(CC) $< $(CCFLAGS) -o $@

clean:
	$(RM) $(OBJS) $(TARGET:.coff=.*) vcd.dsk vcd.rti vcd.toc