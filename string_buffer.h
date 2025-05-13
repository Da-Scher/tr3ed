#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_buffer {
	uint8_t* string;
	size_t  size;
	size_t  cursor_position;
	size_t  array_size;
	size_t  line_position;
} str_buffer;

uint8_t add_to_str_buffer(uint8_t c, str_buffer* sb);

#endif
