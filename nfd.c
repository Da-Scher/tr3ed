#include "nfd.h"

nfd* create_file(int16_t fd, nfd* prev) {
	// TODO: if fd is empty, do we write to stdout?
	//       do we write to nothing?
	if(fd == -1) {
		return NULL;
	}
	nfd* new_file_member = malloc(sizeof(nfd));
	new_file_member->fd  = fd;
	new_file_member->next = NULL;
	new_file_member->prev = prev;
	new_file_member->buffer_tree = NULL;
	return new_file_member;
}
void reap_nfd(nfd* head) {
	if(head == NULL) {
		return;
	}
	reap_nfd(head->next);
	free(head);
	return;
}
