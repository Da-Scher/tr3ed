#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "nfd.h"
#include "ntb.h"
#include "init.h"

typedef struct string_buffer {
	uint8_t* string;
	size_t  size;
	size_t  cursor_position;
	size_t  array_size;
	size_t  line_position;
} str_buffer;

typedef struct command_history {
	uint8_t* string;
	size_t size;
	struct command_history* next;
	struct command_history* prev;
} cmd_hist;

typedef enum {
	NORMAL,
	ESC,
	ESC_BRACKET,
	EDIT_APPEND,
	EDIT_INSERT,
	BAD
} State;

typedef enum {
	NONE,
	WRITE
} State_Process;

void input_loop(nfd* nfd);
State process_line(str_buffer* sb);
cmd_hist* add_command_to_history(str_buffer* sb, cmd_hist* ch);
void clear_line(str_buffer* sb);
void move_cursor(str_buffer* sb, int8_t d);
void append_to_line(nfd* fd, str_buffer* sb);

#endif
