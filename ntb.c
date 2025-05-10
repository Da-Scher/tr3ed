#include "ntb.h"

ntb* create_buffer(str_buffer* sb) {
	// if buffer is empty, make an ntb with only 0's
	if(sb->string == NULL) {
		return calloc(1, sizeof(ntb));
	}
	// make a buffer with an initial buffer
	ntb* new_buffer = malloc(sizeof(ntb));
	new_buffer->buffer = sb->string;
	new_buffer->line = sb->line_position;
	new_buffer->l = NULL;
	new_buffer->r = NULL;
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

void insert_buffer(ntb* root, ntb* buffer) {
	if(buffer->line <= root->line) {
		if(root->l == NULL) root->l = buffer;
		else insert_buffer(root->l, buffer);
	}
	else if(buffer->line > root->line) {
		if(root->r == NULL) root->r = buffer;
		else insert_buffer(root->r, buffer);
	}
}
