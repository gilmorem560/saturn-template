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

CCFLAGS = -O -m2 -g -c -I$(SGLIDR)
LDFLAGS = -T$(LDFILE) -Map $(MPFILE) -e ___Start

SRCS = \
	src/graphics/primitives/grid2d.c \
	src/graphics/primitives/grid3d.c \
	src/graphics/primitives/point2d.c \
	src/graphics/primitives/point3d.c \
	src/graphics/primitives/poly2d.c \
	src/graphics/primitives/poly3d.c \
	src/graphics/primitives/vect.c \
	src/modes/modes.c \
	src/modes/actor_test.c \
	src/modes/actor_test_obj/actors/cube.c \
	src/modes/actor_test_obj/actors/tetrahedron.c \
	src/modes/actor_test_obj/actors/triangle.c \
	src/modes/actor_test_obj/nodes/box.c \
	src/modes/actor_test_obj/nodes/camera.c \
	src/modes/actor_test_obj/nodes/collectible.c \
	src/modes/actor_test_obj/nodes/environment.c \
	src/modes/actor_test_obj/nodes/orbit.c \
	src/modes/actor_test_obj/nodes/player.c \
	src/scene/actor.c \
	src/scene/collision/collision_box.c \
	src/scene/collision/collision_router.c \
	src/scene/node.c \
	src/scene/scene.c \
	src/scene/texture.c \
	src/main.c
OBJS = $(SRCS:.c=.o)
LIBS =  -lmem -lmth -lsgl -lgcc

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
	rm -f game.bin game.cue
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
