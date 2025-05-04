#include "ntb.h"

ntb* create_buffer(uint8_t* buffer) {
	// if buffer is empty, make an ntb with only 0's
	if(buffer == NULL) {
		return calloc(1, sizeof(ntb));
	}
	// make a buffer with an initial buffer
	ntb* new_buffer = malloc(sizeof(ntb));
	new_buffer->buffer = buffer;
	return new_buffer;
}

void reap_ntb(ntb* root) {
	// if root is empty, do nothing
	if(root == NULL) {
		return;
	}
	// Recursively
	reap_ntb(root->l);
	reap_ntb(root->r);
	free(root);
	return;
}
