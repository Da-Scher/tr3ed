#ifndef NFD_H
#define NFD_H

#include <stdint.h>
#include <stdlib.h>

#include "ntb.h"

/* typedef struct node_fd nfd
 * Members
 * int16_t fd -- the file descriptor to be saved.
 * nfd* next -- the next nfd in the double-linked list
 * nfd* prev -- the previous nfd in the double-linked list
**/
typedef struct node_fd {
	int16_t fd;
	struct node_fd* next;
	struct node_fd* prev;
	ntb* buffer_tree;
} nfd;

/* nfd* new_file(int16_t) -- Create a new member of the nfd double-linked list
 * Arguments:
 * int16_t fd -- The file descriptor to be added to the list. 
 * nfd* prev -- the previous node in line (NULL if this is the first of a new linked list)
 *
 * Returns the new member of the double-linked list.
**/
nfd* create_file(int16_t fd, nfd* prev);

/* void reap_nfd(nfd*) -- frees all the memory used by the linked list
 * Arguments:
 * nfd* head -- the first member of the doubly-linked list
 *
 * No return value.
**/
void reap_nfd(nfd* head);

#endif
