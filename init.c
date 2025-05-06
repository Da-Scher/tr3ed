#include "init.h"

void termios_change_mode(uint8_t to_raw) {
	static struct termios oldt;
	struct termios newt;
	
// change mode from canonical to raw
	if(to_raw) {
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;

		newt.c_lflag &= ~(ICANNON | ECHO);

		newt.c_cc[VMIN] = 1;
		newt.c_cc[VTIME] = 0;

		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	}
	else {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	}

}
