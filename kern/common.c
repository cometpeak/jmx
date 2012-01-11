#include "common.h"

void breakpoint(void)
{
	asm volatile ("int3");
}

void outb(uint16_t port, uint8_t data)
{
	asm volatile ("outb %0, %w1" : : "a" (data), "d" (port));
}

uint8_t inb(uint16_t port)
{
	uint8_t data;
	asm volatile ("inb %w1, %0" : "=a" (data) : "d" (port));
	return data;
}

void outw(uint16_t port, uint16_t data)
{
	asm volatile ("outw %0, %w1" : : "a" (data), "d" (port));
}

uint16_t inw(uint16_t port)
{
	uint16_t data;
	asm volatile ("inw %w1, %0" : "=a" (data) : "d" (port));
	return data;
}
