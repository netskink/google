#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "hash.h"
#include "parser.h"

/* this platform has 64 bit integers *
 * the dictionary file I am using has
 * 103266 entries. In hex this less than
 * 0x2 0000
 * So I will try to get a generator 
 * which will make max numbers half 
 * of that so I get collisions which
 * I will handle with a list.
 * but I will limit the number.      
 * grep -E ^[A-Z]+..$ dictionary.txt | wc -l
 * bc
 * obase=16
 */
const int MAXNUM=0xFFFFF;

#ifdef STOCKVERSIONS
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
#endif


int calculateLRC(const char *buffer, unsigned int length){
	// ASCII A is hex 0x41
	// ASCII Q is hex 0x51
	unsigned int checksum = 0;
	int shift_fudge;
	while(length--) {
		checksum += *buffer;
		shift_fudge = (*buffer&0x10)? 8:0;
		checksum = checksum << shift_fudge;	// my own twist
		checksum &= MAXNUM;	// limit number
		buffer++;
	}
	return (((checksum ^ MAXNUM) + 1) & MAXNUM);
}


// This code takes a word (key) and returns the hash table index where the definition can be found.
int f(char *key,int array_size) {
	unsigned int index;
	index = calculateLRC(key, strlen(key));

	printf("index = %x\n",index);
	index = index % array_size;
	printf("modified index = %x\n\n",index);
	return (index);
}

