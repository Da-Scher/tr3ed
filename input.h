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

typedef struct command_history {
	uint8_t string[256];
	size_t size;
	struct command_history* next;
	struct command_history* prev;
} cmd_hist;

typedef enum {
  NORMAL,
  ESC,
  ESC_BRACKET
} State;

typedef enum {
	NONE,
	WRITE
} State_Process;

void input_loop();
int16_t process_line(str_buffer* sb);
cmd_hist* add_command_to_history(str_buffer* sb, cmd_hist* ch);
void clear_line(str_buffer* sb);

#endif
