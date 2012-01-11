
#include "monitor.h"

/*
 * Stores current cursor positions
 */
uint16_t cursor_y = 0;
uint16_t cursor_x = 0;

/*
 * Video frame buffer starts at 0xB800
 */
uint16_t *video_memory = (uint16_t *) 0xb8000;

/**
 * Updates the hardware cursor
 */
static void move_cursor()
{
	uint16_t cursor_location = cursor_y * CRT_COLS + cursor_x;
	outb(0x3D4, 14);
	outb(0x3D5, cursor_location >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursor_location);
}

/**
 * Scrolls the text on the screen up by one line.
 */
static void scroll()
{
	// Get a space character with the default color attributes
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);

	// Row 25 is the end, which means we have to scroll up
	if (cursor_y >= CRT_ROWS) {
		// Move the current text chunk that makes up the screen
		// back in the buffer by one line
		int i;
		for (i = 0 * CRT_COLS; i < (CRT_ROWS - 1) * CRT_COLS; i++) {
			video_memory[i] = video_memory[i + CRT_COLS];
		}

		// The last line should now be blank. Do this by writing 80
		// spaces to it
		for (i = (CRT_ROWS-1)*CRT_COLS; i < CRT_ROWS*CRT_COLS; i++) {
			video_memory[i] = blank;
		}

		// Cursor should now be on the last line
		cursor_y = (CRT_ROWS-1);
	}
}

/**
 * Write a single character to the screen
 *
 * @param c - character to be written to screen
 */
void monitor_put(char c)
{
	// Background color is black
	uint8_t color_back = 0;
	uint8_t color_fore = 15;

	// The attribute byte is made of two parts - the lower being the 
	// foreground color and the upper being the background color
	uint8_t attribute_byte = (color_back << 4) | (color_fore & 0x0F);

	// The attribute byte is the top 8 bits ofo the word we have to
	// send to the VGA board
	uint16_t attribute = attribute_byte << 8;
	uint16_t *location;

	if (c == '\b' && cursor_x > 0) {
		cursor_x--;
	} else if (c == '\t') {
		// Handle a tab by increasing cursor_x, but only to a point where
		// it is divisible by 8
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	} else if (c == '\r') {
		// Carriage return
		cursor_x = 0;
	} else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else if (c >= ' ') {
		location = video_memory + (cursor_y*CRT_COLS + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	// Check to see if we need to insert a new line because we have
	// reached the end of the screen
	if (cursor_x >= CRT_COLS) {
		cursor_x = 0;
		cursor_y++;
	}

	scroll();
	move_cursor();
}


/**
 * Clears the screen by copying lots of spaces to the framebuffer
 */
void monitor_clear()
{
	// Make an attribute byte for the default colors
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);

	int i;
	for (i = 0; i < CRT_COLS*CRT_ROWS; i++)
		video_memory[i] = blank;

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

/**
 * Outputs a null-terminated ASCII string to the monitor
 */
void monitor_write(char *c)
{
	int i = 0;
	while (c[i]) {
		monitor_put(c[i]);
		i++;
	}
}


