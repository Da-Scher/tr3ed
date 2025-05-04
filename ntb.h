#ifndef NTB_H
#define NTB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* typedef struct node_tree_buffer ntb
 * Members
 * uint8_t* buffer -- the character buffer of any potential size
 * ntb* l -- the left child of this node
 * ntb* r -- the right child of this node
**/
typedef struct node_tree_buffer {
	uint8_t* buffer;
	ntb* l;
	ntb* r;
} ntb;

/* ntb* create_buffer(uint8_t*) -- create a new line buffer
 * Arguments:
 *  uint8_t* buffer -- pointer to a new string buffer. (NULL if the new buffer is empty)
 *
 * Returns a new ntb object.
**/
ntb* create_buffer(uint8_t* buffer);


#endif
