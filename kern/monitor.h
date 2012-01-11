#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

#define CRT_ROWS 25
#define CRT_COLS 80
#define CRT_SIZE (CRT_ROWS * CRT_COLS)

/**
 * Write a single character to the screen
 */
void monitor_put(char c);

/**
 * Clear the screen to all black
 */
void monitor_clear(void);

/**
 * Output a null-terminated ASCII string to the monitor
 */
void monitor_write(char *c);

#endif
