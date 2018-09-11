/*
 ============================================================================
 Name        : buffer.c
 Author      : Starkers92
 Version     :
 Copyright   : MIT License
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../buffer/buffer8small.h"

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	//Create buffer
	struct s_buffer8small *MyBuffer = buffer_create8small(10);

	//Write 5 values to buffer
	for (uint8_t write_index = 0; write_index<5; write_index++) {
		buffer_write8small(MyBuffer,write_index);
	}


	//Read 5 values from buffer
	uint8_t read_value;

	for (uint8_t read_index = 0; read_index<5; read_index++) {
		buffer_read8small(MyBuffer,&read_value);
		printf("Value : %d \n",read_value);
	}

	buffer_destroy8small(MyBuffer);

	return EXIT_SUCCESS;
}
