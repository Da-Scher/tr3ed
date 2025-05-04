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

#endif
