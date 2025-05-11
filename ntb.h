#ifndef NTB_H
#define NTB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "string_buffer.h"

/* typedef struct node_tree_buffer ntb
 * Members
 * uint8_t* buffer -- the character buffer of any potential size
 * ntb* l -- the left child of this node
 * ntb* r -- the right child of this node
**/
typedef struct node_tree_buffer {
	uint8_t* buffer;
	int8_t d;
	struct node_tree_buffer* l;
	struct node_tree_buffer* r;
	size_t line;
} ntb;

/* ntb* create_buffer(uint8_t*) -- create a new line buffer
 * Arguments:
 *  uint8_t* buffer -- pointer to a new string buffer. (NULL if the new buffer is empty)
 *
 * Returns a new ntb object.
**/
ntb* create_buffer(str_buffer* sb);

/* void reap_ntb(ntb*) -- deletes the entire ntb buffer tree from root up.
 * Arguments:
 *  ntb* root -- The root of the tree we are reaping.
 *
 * No return value.
**/
void reap_ntb(ntb* root);

void insert_buffer(ntb* root, ntb* buffer);
#endif
