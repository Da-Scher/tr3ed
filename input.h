#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef enum {
  NORMAL,
  ESC,
  ESC_BRACKET
} State;

void input_loop();

#endif
