#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "main.h"


unsigned char calculateLRC(const unsigned char *buffer, unsigned int length){
	unsigned char checksum = 0;
	while(length--) checksum += *buffer++;
	return checksum ^ 0xFF + 1;
}


// This code takes a word (key) and returns the hash table index where the definition can be found.
int f(char *key,int array_size) {
	unsigned char index;
	index = calculateLRC(key, strlen(key));

	printf("index = %x\n",index);
}


