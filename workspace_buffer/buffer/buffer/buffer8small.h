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



#endif /* NUFFER_H_ */
