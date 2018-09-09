/*
 * buffer.c
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */

#include "buffer8small.h"

enum et_buffer_status buffer_write8(struct s_buffer8small *s, uint8_t byte) {
	uint8_t next_index = (((s->u8_newest_index)+1) % s->u8_length);
	if (next_index == s->u8_oldest_index){
		return BUFFER_FULL;
	}
	s->u8a_data[s->u8_newest_index] = byte;
	s->u8_newest_index = next_index;
	s->u8_items_waiting++;
	return BUFFER_OK;
}

enum et_buffer_status buffer_read8(struct s_buffer8small *s, uint8_t *byte){
	if (s->u8_newest_index == s->u8_oldest_index){
		return BUFFER_EMPTY;
	}
	*byte = s->u8a_data[s->u8_oldest_index];
	s->u8_oldest_index = ((s->u8_oldest_index+1) % s->u8_length);
	s->u8_items_waiting--;
	return BUFFER_OK;
}

enum et_buffer_status buffer_peek8(struct s_buffer8small *s, uint8_t *byte){
	uint8_t last_index = ((s->u8_length + (s->u8_newest_index) - 1) % s->u8_length);
	if (s->u8_newest_index == s->u8_oldest_index){
		return BUFFER_EMPTY;
	}
	*byte = s->u8a_data[last_index];
	return BUFFER_OK;
}
