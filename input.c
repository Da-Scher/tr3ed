#include "input.h"
#include "init.h"

void input_loop(nfd* fd) {
	str_buffer* sb = malloc(sizeof(str_buffer));
	uint8_t c;
	sb->string = calloc(8, sizeof(uint8_t));
	sb->array_size = 8;
	sb->size = 0;
	sb->cursor_position = 0;
	State state = NORMAL;
	cmd_hist* ch = NULL;
	// loop forever
	while(read(STDIN_FILENO, &c, 1) == 1) {
		switch(state) {
			case NORMAL:
				// detected an escape key
				if(c=='\x1b') state = ESC;
				// detected an enter key
				else if(c=='\x0a') {
					write(STDOUT_FILENO, &c, 1);
					// add the line to the command history
					ch = add_command_to_history(sb, ch);
					State result = process_line(sb);
					if(result == QUIT) {
						return;
					}
					else if(result == BAD) {
						write(STDOUT_FILENO, "?\n", 3);
					}
					else if(result == EDIT_APPEND) {
						append_to_line(fd, sb);
					}
					else {
						memset(sb->string, 0, sb->size);

					}
				}
				// detected a backspace key
				else if(c=='\x7f') {
					write(STDOUT_FILENO, "\x1b[D\x1b[P", 6);
					if(sb->cursor_position > 0) {
						memmove(sb->string + sb->cursor_position - 1, sb->string + sb->cursor_position, sb->size - sb->cursor_position);
						sb->size--;
						sb->cursor_position--;
					}
				}
				// detected a regular key
				else {
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
					write(STDOUT_FILENO, &c, 1);

				}
				break;
			case ESC:
				if(c=='[') state = ESC_BRACKET;
				else state = NORMAL;
				break;
			case ESC_BRACKET:
				if(c=='A') {
					// printf("Insert arrow-up code here.\n");
					// TODO: remember the non-inputted buffer so that we can use it again if necessary.
					if(ch != NULL) {
						clear_line(sb);
						memcpy(sb->string, ch->string, ch->size);
						sb->size = ch->size;
						sb->cursor_position = ch->size;
						write(STDOUT_FILENO, sb->string, sb->size);
						if(ch->prev != NULL) ch = ch->prev;
					}
				}
				else if(c=='B') { 
					//printf("Insert arrow-down code here.\n");
					if(ch->next != NULL) {
						ch = ch->next;
						clear_line(sb);
						memcpy(sb->string, ch->string, ch->size);
						sb->size = ch->size;
						write(STDOUT_FILENO, sb->string, sb->size);
					}
					else if(ch == NULL) {
						clear_line(sb);
					}
				}
				else if(c=='C') {
					//printf("Insert arrow-right code here.\n");
					move_cursor(sb, 1);
				}
				else if(c=='D') {
					//printf("Insert arrow-left code here.\n");
					move_cursor(sb, -1);
				}
				state = NORMAL;
				break;
			case EDIT_APPEND:
				append_to_line(fd, sb);
				break;
			case EDIT_INSERT:
				break;
				
		}
	}
}

State process_line(str_buffer* sb) {
	State_Process process_state = NONE;
	// why loop here? because in `ed` there should be support for common
	// command sequences, like 'wq', or 'id' for insert at, delete other line. etc
	for(int i = 0; i < sb->size; i++) {
		if(sb->string[i] == 'q') {
			// clear sb->string, set sb->size to 0
			memset(sb->string, 0, sb->size);
			sb->size = 0;
			sb->cursor_position = 0;
			if(process_state == NONE || process_state == WRITE) return QUIT;
			else return BAD;
		}
		else if(sb->string[i] == 'a') {
			if(process_state == NONE || process_state == WRITE) return EDIT_APPEND;
			else return BAD;
		}
		else if(sb->string[i] == 'i') {
			if(process_state == NONE || process_state == WRITE) return EDIT_INSERT;
			else return BAD;
		}
		else {
			memset(sb->string, 0, sb->size);
			sb->size = 0;
			sb->cursor_position = 0;
			return BAD;
		}
	}
	return NORMAL;
}

cmd_hist* add_command_to_history(str_buffer* sb, cmd_hist* ch) {
	// go to the last member of history
	cmd_hist* prev = NULL;
	cmd_hist* curr = ch;
	while(curr != NULL) {
		prev = curr;
		curr = curr->next;
	}
	// create a command history entry
	curr = malloc(sizeof(cmd_hist));
	curr->string = malloc(sizeof(uint8_t)*sb->array_size);
	memcpy(curr->string, sb->string, sb->array_size);
	curr->size = sb->size;
	curr->prev = prev;
	if(prev != NULL) prev->next = curr;
	curr->next = NULL;
	return curr;
}

void clear_line(str_buffer* sb) {
	write(STDOUT_FILENO, "\x1b[2K\x1b[1G", 8);
	memset(sb->string, 0, sb->size);
	sb->size = 0;
	sb->cursor_position = 0;
}

void move_cursor(str_buffer* sb, int8_t d) {
	if(d < 0 && sb->cursor_position > 0) {
		// move one to the left
		write(STDOUT_FILENO, "\x1b[1D", 4);
		sb->cursor_position--;
	}
	else if(d >= 0 && sb->cursor_position < sb->size) {
		// move one to the right
		write(STDOUT_FILENO, "\x1b[1C", 4);
		sb->cursor_position++;
	}
}

void append_to_line(nfd* fd, str_buffer* sb) {
	uint8_t c;
	Edit_State edit_state = NORMAL_EDIT;
	while((read(STDIN_FILENO, &c, 1)) == 1) {
		switch(c) {
			case '\x0a':
				if(edit_state == WRITE_EDIT) {
					return;
				}
				write(STDOUT_FILENO, &c, 1);
				// create node on buffer tree
				ntb* tb = create_buffer(sb);
				if(fd->buffer_tree == NULL) fd->buffer_tree = tb;
				else insert_buffer(fd->buffer_tree, tb);
				sb->line_position++;
				clear_line(sb);
				break;
			case '.':
				write(STDOUT_FILENO, &c, 1);
				if(sb->cursor_position == 0) {
					return;
				}
				sb->string[sb->cursor_position++] = c;
				sb->size++;
				break;
			default:
				// if c is a character
				if(c >= 32 && c < 127) {
					memmove(sb->string + sb->cursor_position, sb->string + sb->cursor_position - 1, sb->size-sb->cursor_position+1);
					write(STDOUT_FILENO, &c, 1);
					sb->string[sb->cursor_position++] = c;
					sb->size++;
				}
				edit_state = NORMAL_EDIT;
				break;
		}
	}
}
