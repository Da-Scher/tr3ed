#include "input.h"

str_buffer sb;

void input_loop() {
<<<<<<< HEAD
<<<<<<< Updated upstream
	// loop forever
	while(1) {
=======
	uint8_t c;
	memset(sb.string, 0, sizeof(sb.string));
	sb.size = 0;
	State state = NORMAL;
	// loop forever
=======
	uint8_t c;
  State state = NORMAL;
	// loop forever
>>>>>>> ad95e4558d2ca7299d8e0cf77fd0ed3ba8f54313
	while(read(STDIN_FILENO, &c, 1) == 1) {
		switch(state) {
			case NORMAL:
				if(c=='\x1b') state = ESC;
<<<<<<< HEAD
				else if(c=='\x0a') {
					int result = process_line(sb.string);
					if(result == 0) {
						return;
					}
					else if(result == -1) {
						printf("?\n");
					}
					else {
						memset(sb.string, 0, sizeof(sb.string));

					}
				}
				else {
					write(STDOUT_FILENO, &c, 1);
					sb.string[sb.size++] = c;

				}
=======
				else if(c=='q') return;
				else write(STDOUT_FILENO, &c, 1);
>>>>>>> ad95e4558d2ca7299d8e0cf77fd0ed3ba8f54313
				break;
			case ESC:
				if(c=='[') state = ESC_BRACKET;
				else state = NORMAL;
				break;
			case ESC_BRACKET:
				if(c=='A') printf("Insert arrow-up code here.\n");
				else if(c=='B') printf("Insert arrow-down code here.\n");
				else if(c=='C') printf("Insert arrow-right code here.\n");
				else if(c=='D') printf("Insert arrow-left code here.\n");
				state = NORMAL;
				break;
<<<<<<< HEAD
>>>>>>> Stashed changes
=======
>>>>>>> ad95e4558d2ca7299d8e0cf77fd0ed3ba8f54313

		}
	}
}
<<<<<<< HEAD
<<<<<<< Updated upstream
=======


int16_t process_line(uint8_t* line) {
	State_Process process_state = NONE;
	for(int i = 0; i < sb.size; i++) {

		if(sb.string[i] == 'q') {
			if(process_state == NONE) return 0;
			else printf("?\n");
		}
	}
	return 1;
}
>>>>>>> Stashed changes
=======

>>>>>>> ad95e4558d2ca7299d8e0cf77fd0ed3ba8f54313
