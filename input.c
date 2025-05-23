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
				switch(c) {
					// detected an escape key
					case '\x1b':
						state = ESC;
					break;
					// detected an enter key
					case '\x0a':
						write(STDOUT_FILENO, &c, 1);
						// add the line to the command history
						ch = add_command_to_history(sb, ch);
						State result = process_line(sb);
						clear_line(sb);
						switch(result) {
							case QUIT:
								return;
							break;
							case BAD:
								write(STDOUT_FILENO, "?\n", 3);
							break;
							case EDIT_APPEND:
								add_edit(fd, sb, 1, sb->line_position);
							break;
							case EDIT_INSERT:
								add_edit(fd, sb, 0, sb->line_position);
							break;
							case DELETE_LINE:
								delete_line(fd, sb->line_position);
							break;
						}
					break;
					// detected a backspace key
					case '\x7f':
						write(STDOUT_FILENO, "\x1b[D\x1b[P", 6);
						if(sb->cursor_position > 0) {
							memmove(sb->string + sb->cursor_position - 1, sb->string + sb->cursor_position, sb->size - sb->cursor_position);
							sb->size--;
							sb->cursor_position--;
						}
					break;
					// detected a regular key
					default:
						if(add_to_str_buffer(c, sb) == 1) {
							write(STDOUT_FILENO, &c, 1);
						}
					break;
				}
				break;
			case ESC:
				if(c=='[') state = ESC_BRACKET;
				else state = NORMAL;
				break;
			case ESC_BRACKET:
				clear_line(sb);
				switch(c) {
				case 'A':
					ch = move_history_pointer(ch, sb, 1);
				break;
				case 'B':
					ch = move_history_pointer(ch, sb, 0);
				break;
				case 'C':
					move_cursor(sb, 1);
				break;
				case 'D':
					move_cursor(sb, -1);
				break;
				default:
				break;
			}
			state = NORMAL;
			break;
		}
	}
}

State process_line(str_buffer* sb) {
	State_Process process_state = NONE;
	State return_state = NORMAL;
	uint8_t d2, d1;
	uint8_t c;
	uint8_t s[100];
	uint8_t leftover[100];
	if(sscanf(sb->string, "%d%99[^\n]", &d2, leftover) == 1) {
		sb->line_position = d2;
		return NORMAL;
	}
	else if(sscanf(sb->string, "%d,%d%99s%99[^\n]", &d1, &d2, s, leftover) == 3) {
		return_state = check_state(s);
		if(return_state == BAD) return BAD;
		else sb->line_position = d2;
		return return_state;
	}
	else if(sscanf(sb->string, "%d%99s%99[^\n]", &d2, s, leftover) == 2) {
		// check validity of string
		return_state = check_state(s);
		if(return_state == BAD) return BAD;
		else sb->line_position = d2;
		return return_state;
	}
	else if(sscanf(sb->string, "%99s%99[^\n]", s, leftover) == 1) {
		return check_state(s);
	}
	
}
State check_state(uint8_t* string) {
	State return_state = NORMAL;
	State_Process process_state = NONE;
	ssize_t len = strlen(string);
	for(int i = 0; i < len; i++) {
		if(string[i] == 'q') {
			if(process_state == NONE || process_state == WRITE) return_state = QUIT;
			else return_state = BAD;
		}
		else if(string[i] == 'd') {
			return_state = DELETE_LINE;
		}
		else if(string[i] == 'a') {
			if(process_state == NONE || process_state == WRITE) return_state = EDIT_APPEND;
			else return_state = BAD;
		}
		else if(string[i] == 'i') {
			if(process_state == NONE || process_state == WRITE) return_state = EDIT_INSERT;
			else return_state = BAD;
		}
		else if(string[i] == 'd') {
			if(process_state == NONE) return_state = DELETE_LINE;
			else return_state = BAD;
		}
	}
	return return_state;
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

void add_edit(nfd* fd, str_buffer* sb, uint8_t append, uint8_t line) {
	uint8_t c;
	Edit_State edit_state = NORMAL_EDIT;
	if(append == 1) sb->line_position += 1;
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

void delete_line(nfd* fd, uint8_t line) {
	if(fd->buffer_tree == NULL) return;
	ntb* curr = fd->buffer_tree;
	ntb* next;
	if(curr->line > line) {
		next = curr->l;
	}
	else if(curr->line < line) {
		next = curr->r;
	}
	else if(curr->line == line) {
		// delete all l children
		delete_rope(curr->l);
		// flag for deletion
		curr->d = 1;
		return;
	}
	while(next != NULL) {
		next = curr->line > line ? curr->r : curr->r;
	}
}

cmd_hist* move_history_pointer(cmd_hist* ch, str_buffer* sb, uint8_t up) {
	// TODO: remember the non-inputted buffer so that we can use it again if necessary.
	clear_line(sb);
	if(ch != NULL) {
		switch(up) {
			case 1:
				memcpy(sb->string, ch->string, ch->size);
				sb->size = ch->size;
				sb->cursor_position = ch->size;
				write(STDOUT_FILENO, sb->string, sb->size);
				if(ch->prev != NULL) ch = ch->prev;
			break;
			default:
				if(ch->next == NULL) break;
				ch = ch->next;
				memcpy(sb->string, ch->string, ch->size);
				sb->size = ch->size;
				write(STDOUT_FILENO, sb->string, sb->size);
			break;
		}
	}
	return ch;
}
