#
# SGL Makefile Template
#

CC = sh-gcc
LD = sh-ld
RM = rm -f
CONV = sh-objcopy

SGLDIR = /usr/sh-saturn-coff
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

all: $(TARGET) $(TARGET1) game.bin

$(TARGET): $(OBJS) $(MAKEFILE) $(LDFILE)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

$(TARGET1): $(OBJS) $(MAKEFILE)
	$(CONV) -O binary $(TARGET) $(TARGET1)

game.iso: $(TARGET1)
	mkisofs -o game.iso $(TARGET1)
	mksatiso game.iso ip.bin
	
game.bin: game.iso
	poweriso convert game.iso -o game.bin -ot bin

$(LDFILE) : $(MAKEFILE)
	echo "Making $(LDFILE)"
	echo "SECTIONS { "			>  $@
	echo "	SLSTART 0x06010000 : { "	>> $@
	echo "		___Start = .; "		>> $@
	echo "		*(SLSTART) "		>> $@
	echo "	} "				>> $@
	echo "}	"				>> $@

.SUFFIXES: .asm

.c.o:
	$(CC) $< $(CCFLAGS) -o $@

clean:
	$(RM) $(OBJS) $(TARGET:.coff=.*) game.iso game.bin game.cue
