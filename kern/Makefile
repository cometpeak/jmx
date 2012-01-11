SOURCES = boot.o common.o monitor.o main.o

CC = i386-elf-gcc
LD = i386-elf-ld
AS = i386-elf-as

CFLAGS = -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
LDFLAGS = -T link.ld
ASFLAGS = 

all: $(SOURCES) link image

clean:
	rm -f *.o kernel floppy.img

distclean:
	rm -f *.o kernel floppy.img bochsout.txt

boot.o:
	$(AS) $(ASFLAGS) boot.s -o boot.o

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

image:
	cat  ./etc/stage1 ./etc/stage2 ./etc/pad kernel > floppy.img

bochs:
	bochs -f bochsrc.txt

qemu:
	qemu -fda floppy.img

pad:
	dd if=/dev/zero of=./etc/pad bs=1 count=750
