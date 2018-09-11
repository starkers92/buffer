/*
 * buffer.c
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */
#include <stdlib.h>
#include "buffer16.h"


struct s_buffer16 *buffer_create16(uint16_t len) {
	struct s_buffer16 *s = malloc( sizeof(*s) + sizeof(uint16_t) * len );
	if(!s) {
		//Malloc failed
		s->u16_length = 0;
	}
	else {
		s->u16_length = len;
	}
	s->u16_newest_index=0;
	s->u16_oldest_index=0;
	s->u16_items_waiting=0;
	return s;
}

void buffer_destroy16(struct s_buffer16 *s) {
	free(s);
	//FIXME add error handler
}

struct s_buffer16 *buffer_resize16(struct s_buffer16 *old_s,uint16_t len) {
	/*
	 * FIXME need to make me data safe // currently this ruins the contents of the buffer
	 */
	struct s_buffer16 *s = realloc(old_s, sizeof(*s) + sizeof(uint16_t) * len );
	if(!s) {
		//Malloc failed
		s->u16_length = 0;
	}
	else {
		s->u16_length = len;
	}
	return s;
}

enum et_buffer_status buffer_write16(struct s_buffer16 *s, uint16_t byte) {
	uint16_t next_index = (((s->u16_newest_index)+1) % s->u16_length);
	if (next_index == s->u16_oldest_index) {
		return BUFFER_FULL;
	}
	s->u16a_data[s->u16_newest_index] = byte;
	s->u16_newest_index = next_index;
	s->u16_items_waiting++;
	return BUFFER_OK;
}

enum et_buffer_status buffer_read16(struct s_buffer16 *s, uint16_t *byte) {
	if (s->u16_newest_index == s->u16_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u16a_data[s->u16_oldest_index];
	s->u16_oldest_index = ((s->u16_oldest_index+1) % s->u16_length);
	s->u16_items_waiting--;
	return BUFFER_OK;
}

enum et_buffer_status buffer_peek16(struct s_buffer16 *s, uint16_t *byte) {
	uint16_t last_index = ((s->u16_length + (s->u16_newest_index) - 1) % s->u16_length);
	if (s->u16_newest_index == s->u16_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u16a_data[last_index];
	return BUFFER_OK;
}

void buffer_empty16(struct s_buffer16 *s) {
	s->u16_newest_index=0;
	s->u16_oldest_index=0;
	s->u16_items_waiting=0;
}
