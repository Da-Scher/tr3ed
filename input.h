#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct string_buffer {
	uint8_t string[256];
	size_t  size;
} str_buffer;

typedef enum {
	NORMAL,
	ESC,
	ESC_BRACKET,
	EDIT
} State;

typedef enum {
	NONE,
	WRITE
} State_Process;

void input_loop();
int16_t process_line(uint8_t* line);

#endif
