SOURCES = boot.o main.o

CC = i386-elf-gcc
LD = i386-elf-ld
AS = nasm

CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS = -Tlink.ld
ASFLAGS = -felf

all: $(SOURCES) link

clean:
	-rm -f *.o kernel

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	$(AS) $(ASFLAGS) $<
