/*
 * buffer.c
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */
#include <stdlib.h>
#include "buffer32.h"


struct s_buffer32 *buffer_create32(uint32_t len) {
	struct s_buffer32 *s = malloc( sizeof(*s) + sizeof(uint32_t) * len );
	if(!s) {
		//Malloc failed
		s->u32_length = 0;
	}
	else {
		s->u32_length = len;
	}
	s->u32_newest_index=0;
	s->u32_oldest_index=0;
	s->u32_items_waiting=0;
	return s;
}

void buffer_destroy32(struct s_buffer32 *s) {
	free(s);
	//FIXME add error handler
}

struct s_buffer32 *buffer_resize32(struct s_buffer32 *old_s,uint32_t len) {
	/*
	 * FIXME need to make me data safe // currently this ruins the contents of the buffer
	 */
	struct s_buffer32 *s = realloc(old_s, sizeof(*s) + sizeof(uint32_t) * len );
	if(!s) {
		//Malloc failed
		s->u32_length = 0;
	}
	else {
		s->u32_length = len;
	}
	return s;
}

enum et_buffer_status buffer_write32(struct s_buffer32 *s, uint32_t byte) {
	uint32_t next_index = (((s->u32_newest_index)+1) % s->u32_length);
	if (next_index == s->u32_oldest_index) {
		return BUFFER_FULL;
	}
	s->u32a_data[s->u32_newest_index] = byte;
	s->u32_newest_index = next_index;
	s->u32_items_waiting++;
	return BUFFER_OK;
}

enum et_buffer_status buffer_read32(struct s_buffer32 *s, uint32_t *byte) {
	if (s->u32_newest_index == s->u32_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u32a_data[s->u32_oldest_index];
	s->u32_oldest_index = ((s->u32_oldest_index+1) % s->u32_length);
	s->u32_items_waiting--;
	return BUFFER_OK;
}

enum et_buffer_status buffer_peek32(struct s_buffer32 *s, uint32_t *byte) {
	uint32_t last_index = ((s->u32_length + (s->u32_newest_index) - 1) % s->u32_length);
	if (s->u32_newest_index == s->u32_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u32a_data[last_index];
	return BUFFER_OK;
}

void buffer_empty32(struct s_buffer32 *s) {
	s->u32_newest_index=0;
	s->u32_oldest_index=0;
	s->u32_items_waiting=0;
}
