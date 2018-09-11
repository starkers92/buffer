/*
 * buffer.h
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>


enum et_buffer_status {BUFFER_OK, BUFFER_EMPTY, BUFFER_FULL};

struct s_buffer8large {
	uint16_t u16_newest_index;
	uint16_t u16_oldest_index;
	uint16_t u16_items_waiting;
	uint16_t u16_length;
	uint8_t u8a_data[];
};

struct s_buffer8large *buffer_create8large(uint16_t len);
void buffer_destroy8large(struct s_buffer8large *s);
struct s_buffer8large *buffer_resize8large(struct s_buffer8large *old_s,uint16_t len);
enum et_buffer_status buffer_write8large(struct s_buffer8large *s, uint8_t byte);
enum et_buffer_status buffer_read8large(struct s_buffer8large *s, uint8_t *byte);
enum et_buffer_status buffer_peek8large(struct s_buffer8large *s, uint8_t *byte);
void buffer_empty8large(struct s_buffer8large *s);

#endif /* NUFFER_H_ */
