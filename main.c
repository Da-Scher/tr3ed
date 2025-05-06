/* Author: Dakota Schaeffer
 * GH Handle: Da-Scher
 * Date: 5/3/25
 * Note: Lovingly crafted in ed
**/
#include <stdio.h>
#include <stdint.h>

#include "nfd.h"
#include "ntb.h"
#include "init.h"

int32_t main(uint32_t argc, uint8_t **argv) {
  struct termios* oldt = termios_change_mode(1, NULL);
  // rest of code here.
  termios_change_mode(0, oldt);
  return 0;
}
