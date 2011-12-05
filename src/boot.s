;
; boot.s
;
; Kernel start location. Also defines multiboot header.
;

MBOOT_PAGE_ALIGN   equ 1<<0       ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO     equ 1<<1       ; Privde kernel with memory info
MBOOT_HEADER_MAGIC equ 0x1BADB002 ; Multiboot Magic value to identify the kernel
                                  ; as multiboot-compatible
; Note: MBOOT_AOUT_KLUDGE is not used. It means that GRUB does not provide
;       us with a symbol table. We don't need to use this because we are using
;       the ELF format

; MBOOT_PAGE_ALIGN - Ask GRUB to page-align all kernel sections
; MBOOT_MEM_INFO   - Give us some memory information
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM     equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                         ; All instructions should be 32-bit

[GLOBAL mboot]                    ; Make 'mboot' accessible from C
[EXTERN code]                     ; Start of .text section
[EXTERN bss]                      ; Start of .bss section
[EXTERN end]                      ; End of last loadable section

; This is used to embed a header structure in our kernel to comply with
; multiboot. The 'dd' command is a NASM command that allows us to specify
; these constants. The code, bss, end, and start constants are defined by the
; linker
mboot:
	dd MBOOT_HEADER_MAGIC     ; GRUB will search for this value on each
	                          ; 4-byte boundary in kernel file
	dd MBOOT_HEADER_FLAGS     ; How GRUB should load file/settings
	dd MBOOT_CHECKSUM         ; To ensure above values are correct

	dd mboot                  ; Location of this descriptor
	dd code                   ; Start of kernel .text (code) section
	dd bss                    ; End of kernel .data section
	dd end                    ; End of kernel
	dd start                  ; Kernel entry point (initial EIP)

[GLOBAL start]                    ; Kernel entry point
[EXTERN main]                     ; Entry point for C code

; During boot, GRUB will load a pointer to ebx that may be used to query the
; environment that GRUB sets up.
start:
	push ebx                  ; Load multiboot header location

	; Execute kernel
	cli                       ; Disable interrupts
	call main                 ; Call main() function
	jmp $                     ; Shouldn't return. Enter infinite loop
	                          ; We don't want processor to execute
				  ; garbage in memory that comes after kernel
