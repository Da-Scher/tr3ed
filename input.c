#include "input.h"

void input_loop() {
	uint8_t c;
  State state = NORMAL;
	// loop forever
	while(read(STDIN_FILENO, &c, 1) == 1) {
		switch(state) {
			case NORMAL:
				if(c=='\x1b') state = ESC;
				else if(c=='q') return;
				else write(STDOUT_FILENO, &c, 1);
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

		}
	}
}

