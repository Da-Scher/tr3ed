#ifndef NFD_H
#define NFD_H

#include <stdint.h>
#include <stdlib.h>

/* typedef struct node_fd nfd
 * Members
 * int16_t fd -- the file descriptor to be saved.
 * nfd* next -- the next nfd in the double-linked list
 * nfd* prev -- the previous nfd in the double-linked list
**/
typedef struct node_fd {
	int16_t fd;
	nfd* next;
	nfd* prev;
} nfd

/* nfd* new_file(int16_t) -- Create a new member of the nfd double-linked list
 * Arguments:
 * int16_t fd -- The file descriptor to be added to the list. 
 *
 * Returns the new member of the double-linked list.
**/
nfd* new_file(int16_t fd);

#endif
