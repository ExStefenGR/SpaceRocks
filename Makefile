#
# Spacerocks.mak
#
# tilemap text via tonclib
#
# NOTE: for educational purposes only. For real work, use 
# devkitPro's templates ( $(DEVKITPRO)/examples/gba/template )
# or tonclib's templates ( $(TONCCODE)/lab/template )

PATH := $(DEVKITARM)/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := main
TITLE   := $(PROJ)

LIBTONC	:= ../../tonclib

INCLUDE  := -I$(LIBTONC)/include
LIBPATHS := -L$(LIBTONC)/lib

LIBS    := -ltonc

COBJS   := $(PROJ).o mainMenu.o playButton.o game.o playerSprite.o gameOverScreen.o pauseMenu.o enemySprite.o shoot.o healthBar0.o healthBar1.o healthBar2.o healthBar3.o enemySpriteExploding.o enemySpriteExploding2.o enemySpriteExploding3.o enemySpriteExploding4.o healthPowerUp.o speedPowerUp.o bulletPowerUp.o

OBJS    := $(COBJS)

# --- boot type (MB=0 : normal. MB=1 : multiboot) ---

MB = 0

ifeq ($(MB),1)

TARGET	:= $(PROJ).mb
SPECS	:= -specs=gba_mb.specs

else

TARGET	:= $(PROJ)
SPECS	:= -specs=gba.specs

endif

# --- Compiling -------------------------------------------------------

CROSS	?= arm-none-eabi-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc
OBJCOPY	:= $(CROSS)objcopy


ARCH	:= -mthumb-interwork -mthumb

ASFLAGS	:= -mthumb-interwork
CFLAGS	:= $(ARCH) $(INCLUDE) -O2 -Wall -fno-strict-aliasing
LDFLAGS	:= $(ARCH) $(SPECS) $(LIBPATHS) $(LIBS) -Wl,-Map,$(PROJ).map

.PHONY : build clean

# --- Build -----------------------------------------------------------

build : $(TARGET).gba


$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(TITLE)

$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

$(COBJS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
# --- Clean -----------------------------------------------------------

clean : 
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o

#EOF
