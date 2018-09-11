/*
 * buffer.c
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */
#include <stdlib.h>
#include "buffer8large.h"


struct s_buffer8large *buffer_create8large(uint16_t len) {
	struct s_buffer8large *s = malloc( sizeof(*s) + sizeof(uint8_t) * len );
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

void buffer_destroy8large(struct s_buffer8large *s) {
	free(s);
	//FIXME add error handler
}

struct s_buffer8large *buffer_resize8large(struct s_buffer8large *old_s,uint16_t len) {
	/*
	 * FIXME need to make me data safe // currently this ruins the contents of the buffer
	 */
	struct s_buffer8large *s = realloc(old_s, sizeof(*s) + sizeof(uint8_t) * len );
	if(!s) {
		//Malloc failed
		s->u16_length = 0;
	}
	else {
		s->u16_length = len;
	}
	return s;
}

enum et_buffer_status buffer_write8large(struct s_buffer8large *s, uint8_t byte) {
	uint16_t next_index = (((s->u16_newest_index)+1) % s->u16_length);
	if (next_index == s->u16_oldest_index) {
		return BUFFER_FULL;
	}
	s->u8a_data[s->u16_newest_index] = byte;
	s->u16_newest_index = next_index;
	s->u16_items_waiting++;
	return BUFFER_OK;
}

enum et_buffer_status buffer_read8large(struct s_buffer8large *s, uint8_t *byte) {
	if (s->u16_newest_index == s->u16_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u8a_data[s->u16_oldest_index];
	s->u16_oldest_index = ((s->u16_oldest_index+1) % s->u16_length);
	s->u16_items_waiting--;
	return BUFFER_OK;
}

enum et_buffer_status buffer_peek8large(struct s_buffer8large *s, uint8_t *byte) {
	uint16_t last_index = ((s->u16_length + (s->u16_newest_index) - 1) % s->u16_length);
	if (s->u16_newest_index == s->u16_oldest_index) {
		return BUFFER_EMPTY;
	}
	*byte = s->u8a_data[last_index];
	return BUFFER_OK;
}

void buffer_empty8large(struct s_buffer8large *s) {
	s->u16_newest_index=0;
	s->u16_oldest_index=0;
	s->u16_items_waiting=0;
}
