/*
 * buffer.c
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */
#include <stdlib.h>
#include "buffer8small.h"


struct s_buffer8small *buffer_create8small(uint8_t len) {
	struct s_buffer8small *s = malloc( sizeof(*s) + sizeof(uint8_t) * len );
	if(!s) {
		//Malloc failed
		s->u8_length = 0;
	}
	else {
		s->u8_length = len;
	}
	s->u8_newest_index=0;
	s->u8_oldest_index=0;
	s->u8_items_waiting=0;
	return s;
}

void buffer_destroy8small(struct s_buffer8small *s) {
	free(s);
	//FIXME add error handler
}

struct s_buffer8small *buffer_resize8small(struct s_buffer8small *old_s,uint8_t len) {
	/*
	 * FIXME need to make me data safe // currently this ruins the contents of the buffer
	 */
	struct s_buffer8small *s = realloc(old_s, sizeof(*s) + sizeof(uint8_t) * len );
	if(!s) {
		//Malloc failed
		s->u8_length = 0;
	}
	else {
		s->u8_length = len;
	}
	return s;
}

enum et_buffer_status buffer_write8small(struct s_buffer8small *s, uint8_t byte) {
	uint8_t next_index = (((s->u8_newest_index)+1) % s->u8_length);
	if (next_index == s->u8_oldest_index) {
		return BUFFER_FULL;
	}
	s->u8a_data[s->u8_newest_index] = byte;
	s->u8_newest_index = next_index;
	s->u8_items_waiting++;
	return BUFFER_OK;
}

enum et_buffer_status buffer_read8small(struct s_buffer8small *s, uint8_t *byte) {
	if (s->u8_newest_index == s->u8_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u8a_data[s->u8_oldest_index];
	s->u8_oldest_index = ((s->u8_oldest_index+1) % s->u8_length);
	s->u8_items_waiting--;
	return BUFFER_OK;
}

enum et_buffer_status buffer_peek8small(struct s_buffer8small *s, uint8_t *byte) {
	uint8_t last_index = ((s->u8_length + (s->u8_newest_index) - 1) % s->u8_length);
	if (s->u8_newest_index == s->u8_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u8a_data[last_index];
	return BUFFER_OK;
}

void buffer_empty8small(struct s_buffer8small *s) {
	s->u8_newest_index=0;
	s->u8_oldest_index=0;
	s->u8_items_waiting=0;
}
