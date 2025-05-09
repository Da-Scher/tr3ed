#include "input.h"

void input_loop() {
	str_buffer* sb = malloc(sizeof(str_buffer));
	uint8_t c;
	memset(sb->string, 0, sizeof(sb->string));
	sb->size = 0;
	State state = NORMAL;
	cmd_hist* ch = NULL;
	// loop forever
	while(read(STDIN_FILENO, &c, 1) == 1) {
		switch(state) {
			case NORMAL:
				if(c=='\x1b') state = ESC;
				else if(c=='\x0a') {
					write(STDOUT_FILENO, &c, 1);
					// add the line to the command history
					ch = add_command_to_history(sb, ch);
					int result = process_line(sb);
					if(result == 0) {
						return;
					}
					else if(result == -1) {
						write(STDOUT_FILENO, "?\n", 3);
					}
					else {
						memset(sb->string, 0, sizeof(sb->string));

					}
				}
				else {
					write(STDOUT_FILENO, &c, 1);
					sb->string[sb->size++] = c;

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
					printf("Insert arrow-right code here.\n");
				}
				else if(c=='D') {
					printf("Insert arrow-left code here.\n");
				}
				state = NORMAL;
				break;
		}
	}
}

int16_t process_line(str_buffer* sb) {
	State_Process process_state = NONE;
	for(int i = 0; i < sb->size; i++) {
		if(sb->string[i] == 'q') {
			// clear sb->string, set sb->size to 0
			memset(sb->string, 0, sb->size);
			sb->size = 0;
			if(process_state == NONE || process_state == WRITE) return 0;
			else return -1;
		}
		else {
			memset(sb->string, 0, sb->size);
			sb->size = 0;
			return -1;
		}
	}
	return 1;
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
	memcpy(curr->string, sb->string, 256);
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
}
