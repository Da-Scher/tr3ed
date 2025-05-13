#include "string_buffer.h"

uint8_t add_to_str_buffer(uint8_t c, str_buffer* sb) {
	if(c < 32 || c > 127) {
		return 0;
	}
	if(sb->cursor_position == sb->array_size) {
		uint8_t* cache = malloc(sizeof(uint8_t) * sb->size + 1);
		memcpy(cache, sb->string, sb->size);
		memmove(cache + sb->cursor_position, cache + sb->cursor_position - 1, sb->size + 1 - sb->cursor_position);
		free(sb->string);
		sb->string = cache;
	}
	else {
		memmove(sb->string + sb->cursor_position, sb->string + sb->cursor_position - 1, sb->size-sb->cursor_position+1);
	}
	sb->string[sb->cursor_position++] = c;
	sb->size++;
	sb->array_size++;
	return 1;
}
