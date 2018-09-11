/*
 * buffer.h
 *
 *  Created on: 5 Aug. 2018
 *      Author: Chris
 */

#ifndef BUFFER_BUFFER32_H_
#define BUFFER_BUFFER32_H_

#include <stdint.h>


enum et_buffer_status {BUFFER_OK, BUFFER_EMPTY, BUFFER_FULL};

struct s_buffer32 {
	uint16_t u32_newest_index;
	uint16_t u32_oldest_index;
	uint16_t u32_items_waiting;
	uint16_t u32_length;
	uint16_t u32a_data[];
};

struct s_buffer32 *buffer_create32(uint32_t len);
void buffer_destroy32(struct s_buffer32 *s);
struct s_buffer32 *buffer_resize32(struct s_buffer32 *old_s,uint32_t len);
enum et_buffer_status buffer_write32(struct s_buffer32 *s, uint32_t byte);
enum et_buffer_status buffer_read32(struct s_buffer32 *s, uint32_t *byte);
enum et_buffer_status buffer_peek32(struct s_buffer32 *s, uint32_t *byte);
void buffer_empty32(struct s_buffer32 *s);


#endif /* BUFFER_H_ */
