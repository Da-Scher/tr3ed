#ifndef INIT_H
#define INIT_H

#include <termios.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* struct termios* termios_change_mode(uint8_t) -- swap terminal mode from canonical to raw or raw to canonical.
 * Arguments:
 * 	uint8_t to_raw -- change the terminal mode to 'raw'.
 *  struct termios* oldt -- the old terminal settings to swap to
 *
 * Returns the pointer to the old terminal settings.
**/
struct termios* termios_change_mode(uint8_t to_raw, struct termios* oldt);
#endif
