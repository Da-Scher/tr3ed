/* Author: Dakota Schaeffer
 * GH Handle: Da-Scher
 * Date: 5/3/25
 * Note: Lovingly crafted in ed
**/
#include <stdio.h>
#include <stdint.h>

/* typedef struct node_tree_buffer ntb
 * Members:
 * uint8_t* buffer -- the first element in a string of buffer changes
 * ntb* left -- left child
 * ntb* right -- right child
**/
typedef struct node_tree_buffer {
	uint8_t* buffer;
	ntb* left;
	ntb* right;
} ntb;

int32_t main(uint32_t argc, uint8_t **argv) {
	return 0;
}
