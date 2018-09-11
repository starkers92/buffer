/*
 * buffer.h
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */

#ifndef BUFFER_BUFFER16_H_
#define BUFFER_BUFFER16_H_

#include <stdint.h>


enum et_buffer_status {BUFFER_OK, BUFFER_EMPTY, BUFFER_FULL};

struct s_buffer16 {
	uint16_t u16_newest_index;
	uint16_t u16_oldest_index;
	uint16_t u16_items_waiting;
	uint16_t u16_length;
	uint16_t u16a_data[];
};

struct s_buffer16 *buffer_create16(uint16_t len);
void buffer_destroy16(struct s_buffer16 *s);
struct s_buffer16 *buffer_resize16(struct s_buffer16 *old_s,uint16_t len);
enum et_buffer_status buffer_write16(struct s_buffer16 *s, uint16_t byte);
enum et_buffer_status buffer_read16(struct s_buffer16 *s, uint16_t *byte);
enum et_buffer_status buffer_peek16(struct s_buffer16 *s, uint16_t *byte);
void buffer_empty16(struct s_buffer16 *s);


#endif /* BUFFER_H_ */
