
#include "monitor.h"

int kmain(void* mbd, unsigned int magic)
{
	if (magic != 0x2BADB002) {
		/* Something went not according to specs. Print an error */
		/* message and halt, but do *not* rely on the multiboot */
		/* data structure. */

		return 0xDEADBABE;

	}
 	/* You could either use multiboot.h */
	/* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
	/* or do your offsets yourself. The following is merely an example. */ 

	char *boot_loader_name = (char*) ((long*) mbd)[16];
	boot_loader_name = 0;

	unsigned char *videoram = (unsigned char *) 0xb8000;

	monitor_clear();

	videoram[0] = 65; /* character 'A' */
	videoram[1] = 0x07; /* light grey (7) on black (0). */

	monitor_clear();

	//monitor_write("hello");
	monitor_put('H');

	//char str[] = "hello";
	//monitor_put('e');
	//monitor_write(str);

	monitor_write("hello");

	return 0;
}
