#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "list.h"
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
#define MAXNUM_D 0xFFFFF
const int MAXNUM=MAXNUM_D;

// The hash table array.  Each entry in this array is a list.
// word entries (word+definition) will be stored in the linked list of the
// individual elements.  The elements are chosen by the index which
// is a function of the hash of the definition word.
static list_t *hash_table[MAXNUM_D];

#ifdef STOCKVERSIONS
/*
 * These are the stock routines from wikipedia for making an 8bit CRC.
 * I want to spread out my indexes to 16 bits so I tweaked it some so
 * that I would not have such long linked lists.
 */
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

//	printf("index = %x\n",index);
	index = index % array_size;
//	printf("modified index = %x\n\n",index);
	return (index);
}

int init_hash_table(void) {
	int i;
	list_t *pList;

	for(i=0;i<MAXNUM;i++) {
		pList = init_list();
		if (NULL == pList) {
			fprintf(stderr, "error in list create.\n");
			exit(-1);
		}
		hash_table[i]=pList;
	}	

	return (0);
}

int insert_word_into_hashtable(int index, word_entry_t *pWordEntry) {
	append(hash_table[index],pWordEntry);
	return (0);
}

int dump_hashtable(void) {
	int i;
	node_t *pNode;


	for(i=0;i<MAXNUM;i++) {
		pNode = hash_table[i]->pFirst;
		if (NULL != pNode) {
			printf("****  Words at hash index i = %x ******\n",i);
			while(NULL != pNode) {
				printf("list word => %s\n",((word_entry_t*) pNode->pData)->word);
				printf("list defn => %s\n\n",((word_entry_t*) pNode->pData)->defn);
				pNode = pNode->pNext;
			}	
		} 
	}
	return(0);
}

int lookupWordLower(char *pWord) {
	int i;
	node_t *pNode;
	char *pPossibleWord;


	i = f(pWord,0x10000);
	pNode = hash_table[i]->pFirst;

	if (NULL != pNode) {
		while(NULL != pNode) {
			pPossibleWord = (char *)((word_entry_t*) pNode->pData)->word;
			if (0 == strcmp(pPossibleWord,pWord)) {
				printf("word => %s\n",((word_entry_t*) pNode->pData)->word);
				printf("defn => %s\n\n",((word_entry_t*) pNode->pData)->defn);
				return (0);
			} 
			pNode = pNode->pNext;
		}	
	} 
	return(1);
}


