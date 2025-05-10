/* Author: Dakota Schaeffer
 * GH Handle: Da-Scher
 * Date: 5/3/25
 * Note: Lovingly crafted in ed
**/
#include <stdio.h>
#include <stdint.h>

#include "nfd.h"
#include "init.h"
#include "input.h"

int32_t main(uint32_t argc, uint8_t **argv) {
  struct termios* oldt = termios_change_mode(1, NULL);
  nfd* fd = create_file(STDOUT_FILENO, NULL);
  // rest of code here.
  input_loop(fd);
  termios_change_mode(0, oldt);
  return 0;
}
