#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "hash.h"
#include "list.h"
#include "io.h"
#include "stack.h"
#include "unit.h"
#include "dictionary.h"


extern stack_t STACK;

int main(int argc, char *argv[]) {

	int iRC;
	char pFindWord[80];

	iRC=EXIT_SUCCESS;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		iRC=EXIT_FAILURE;
		exit(iRC);
	}


	
#ifdef thomas
#endif	

	init_hash_table();

	ReadFile(argv[1]);

//	dump_hashtable();

	// Now that dictionary is hashed,
	// look up some words.

	strcpy(pFindWord,"AMMA");
	if (0 != lookupWord(pFindWord)) {
		printf("%s is not found.\n\n",pFindWord);
	} 


	strcpy(pFindWord,"AMMETER");
	if (0 != lookupWord(pFindWord)) {
		printf("%s is not found.\n\n",pFindWord);
	} 

	strcpy(pFindWord,"AMPMETER");
	if (0 != lookupWord(pFindWord)) {
		printf("%s is not found.\n\n",pFindWord);
	} 

	strcpy(pFindWord,"VOLTMETER");
	if (0 != lookupWord(pFindWord)) {
		printf("%s is not found.\n\n",pFindWord);
	} 

	strcpy(pFindWord,"MAGPIE");
	if (0 != lookupWord(pFindWord)) {
		printf("%s is not found.\n\n",pFindWord);
	} 






	// Stack final check.  This code should never print anything.
	while (stack_not_empty(&STACK)) {
		printf("main.c->%s",pop(&STACK));
	}
	
	exit(iRC);

}



