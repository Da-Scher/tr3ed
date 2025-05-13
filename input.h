#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "nfd.h"
#include "ntb.h"
#include "init.h"
#include "string_buffer.h"

typedef struct command_history {
	uint8_t* string;
	size_t size;
	struct command_history* next;
	struct command_history* prev;
} cmd_hist;

typedef enum {
	NORMAL,
	ESC,
	ESC_BRACKET,
	EDIT_APPEND,
	EDIT_INSERT,
	BAD,
	QUIT,
	DELETE_LINE
} State;

typedef enum {
	NONE,
	WRITE
} State_Process;

typedef enum {
	NORMAL_EDIT,
	WRITE_EDIT
} Edit_State;
	

/* void input_loop(nfd*) -- The primary loop for parsing input.
 * Arguments:
 *  nfd* fd -- The file descriptor we are writing to the buffer of.
 * No return value.
**/ 
void input_loop(nfd* nfd);

/* State process_line(str_buffer*) -- Processing commands from the string_buffer struct.
 * Arguments:
 *  str_buffer* sb -- The string_buffer struct that we are processing for commands.
 * Returns the appropriate State given a string_buffer struct.
**/
State process_line(str_buffer* sb);

/* cmd_hist* add_command_to_history(str_buffer*, cmd_hist*) -- Add a command to the command_history struct
 * Arguments:
 *  str_buffer* sb -- the string buffer that contains the command to be added to cmd_hist.
 *  cmd_hist* ch   -- the command_history struct that we are adding to.
 * Returns the latest member of the command history.
**/
cmd_hist* add_command_to_history(str_buffer* sb, cmd_hist* ch);

/* void clear_line(str_buffer*) -- Clears the str_buffer, setting values to 0.
 * Arguments:
 *  str_buffer* sb -- The string buffer to be cleared.
 * No return value.
**/ 
void clear_line(str_buffer* sb);

/* void move_cursor(str_buffer*, int8_t) -- Moves the cursor one character left or right.
 * Arguments:
 *  str_buffer* sb -- The string buffer we are moving the cursor of.
 *  int8_t d       -- The direction we are moving. < 0 for left, >= 0 for right.
 * No return value. 
**/
void move_cursor(str_buffer* sb, int8_t d);

/* void add_edit(nfd*, str_buffer*, uint8_t, uint8_t) -- add an edit to the provided nfd.
 * Arguments:
 *  nfd* fd -- the file descriptor node we are editing
 *  str_buffer* sb -- the string buffer we're reading for edits
 *  uint8_t append -- append line flag
 *  uint8_t line -- the starting line for editing.
 * No return value
**/
void add_edit(nfd* fd, str_buffer* sb, uint8_t append, uint8_t line);

/* void delete_line(nfd*, uint8_t) -- delete a line in the provided nfd
 * Arguments:
 *  nfd* fd -- the file descriptor node we are editing
 *  uint8_t line -- the line to be deleted
**/
void delete_line(nfd* fd, uint8_t line);

/* State check_state(uint8_t*) -- checks the State that the provided string would result in.
 * Arguments:
 *  uint8_t* string -- the string
 * Returns the State in the instructions in the string.
**/
State check_state(uint8_t* string);

/* cmd_hist* move_history_pointer(cmd_hist*, str_buffer*, uint8_t) -- moves history up or down
 * Arguments:
 *  cmd_hist* ch -- The command history we want to move in
 *  str_buffer* sb -- the string buffer that will be repopulated as we change history
 *  uint8_t up -- the up flag, 1 for up (previous), 0 for down (recent)
 * Returns the next or previous command in history.
**/ 
cmd_hist* move_history_pointer(cmd_hist* ch, str_buffer* sb, uint8_t up);

#endif
