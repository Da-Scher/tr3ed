#include "init.h"

struct termios* termios_change_mode(uint8_t to_raw, struct termios* oldt) {
	struct termios newt;
	if(oldt == NULL) oldt = malloc(sizeof(struct termios));
	
// change mode from canonical to raw
	if(to_raw) {
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;

		newt.c_lflag &= ~(ICANNON | ECHO);

		newt.c_cc[VMIN] = 1;
		newt.c_cc[VTIME] = 0;

		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		return oldt;

	}
	else {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		return oldt;
	}

}

