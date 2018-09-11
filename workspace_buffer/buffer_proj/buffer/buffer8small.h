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

struct s_buffer8small {
	uint8_t u8_newest_index;
	uint8_t u8_oldest_index;
	uint8_t u8_items_waiting;
	uint8_t u8_length;
	uint8_t u8a_data[];
};

struct s_buffer8small *buffer_create8small(uint8_t len);
void buffer_destroy8small(struct s_buffer8small *s);
struct s_buffer8small *buffer_resize8small(struct s_buffer8small *old_s,uint8_t len);
enum et_buffer_status buffer_write8small(struct s_buffer8small *s, uint8_t byte);
enum et_buffer_status buffer_read8small(struct s_buffer8small *s, uint8_t *byte);
enum et_buffer_status buffer_peek8small(struct s_buffer8small *s, uint8_t *byte);
void buffer_empty8small(struct s_buffer8small *s);


#endif /* NUFFER_H_ */
