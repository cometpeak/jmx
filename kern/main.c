
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

	monitor_clear();
	monitor_write("Hello from kernel land\n");
	monitor_write(boot_loader_name);

	return 0;
}
