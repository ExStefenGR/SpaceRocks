PATH := $(DEVKITARM)/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := main
TITLE   := $(PROJ)

# Use absolute paths based on DEVKITPRO.
LIBTONC := $(DEVKITPRO)/libtonc
LIBGBA  := $(DEVKITPRO)/libgba

# Include both libgba and libtonc headers.
INCLUDE  := -I$(LIBGBA)/include -I$(LIBTONC)/include
LIBPATHS := -L$(LIBTONC)/lib

LIBS    := -ltonc

# List all C source object files (e.g. main.c produces main.o, etc.)
COBJS   := main.o mainMenu.o playButton.o game.o playerSprite.o gameOverScreen.o pauseMenu.o enemySprite.o shoot.o healthBar0.o healthBar1.o healthBar2.o healthBar3.o enemySpriteExploding.o enemySpriteExploding2.o enemySpriteExploding3.o enemySpriteExploding4.o healthPowerUp.o bulletPowerUp.o

OBJS    := $(COBJS)

# --- Boot type (MB=0: normal; MB=1: multiboot) -------------------------

MB = 0

ifeq ($(MB),1)
TARGET  := $(PROJ).mb
SPECS   := -specs=gba_mb.specs
else
TARGET  := $(PROJ)
SPECS   := -specs=gba.specs
endif

# --- Compiling -------------------------------------------------------

CROSS   ?= arm-none-eabi-
AS      := $(CROSS)as
CC      := $(CROSS)gcc
LD      := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy

ARCH    := -mthumb-interwork -mthumb

ASFLAGS := -mthumb-interwork
# Removed -flto to avoid objcopy errors with LTO output.
CFLAGS  := $(ARCH) $(INCLUDE) -O3 -ffunction-sections -fdata-sections -Wall -Wextra -fomit-frame-pointer -fno-strict-aliasing -DNDEBUG -ffast-math
LDFLAGS := $(ARCH) $(SPECS) $(LIBPATHS) $(LIBS) -Wl,--gc-sections -Wl,-Map,$(PROJ).map -Wl,--strip-all

.PHONY: build clean

# --- Build -----------------------------------------------------------

build: $(TARGET).gba

$(TARGET).gba: $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
#	-@gbafix $@ -t$(TITLE)

$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

# Standard pattern rule to compile .c files into .o files.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Clean -----------------------------------------------------------

clean:
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o

#EOF
