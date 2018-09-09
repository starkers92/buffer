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

	struct s_buffer8small MyBuffer8Small {
		0,
		0,
		0,
		10,
		10
	};

	return EXIT_SUCCESS;
}
