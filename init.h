#ifndef INIT_H
#define INIT_H

#include <termios.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/* void termios_change_mode(uint8_t) -- swap terminal mode from canonical to raw or raw to canonical.
 * Arguments:
 * 	uint8_t to_raw -- change the terminal mode to 'raw'.
 * 
 * No return value.
**/
void termios_change_mode(uint8_t to_raw);
#endif
